#ifndef _ALLOCATOR_H_
#define _ALLOCATOR_H_

namespace cth
{
	class CrtAllocator {
	public:
		static bool const isNeedFree=false;
		void* Malloc(size_t size)
		{
			return malloc(size);
		}

		void* Realloc(void* destPtr,size_t newSize)
		{
			return realloc(destPtr,newSize);
		}

		void Free(void* ptr)
		{
			free(ptr);
		}
	};

	static const int DefaultChunkCapacity=64*1024;

	template <typename BaseAllocator = CrtAllocator>
	class MemoryPoolAllocator 
	{
	public:
		MemoryPoolAllocator(size_t chunkCapacity_=DefaultChunkCapacity,BaseAllocator* allocator_=NULL) 
		{
			chunkHeader=NULL;
			chunkCapacity=chunkCapacity_;
			if (!allocator){
				allocator=new BaseAllocator();
			}else{
				allocator=allocator_;
			}
			AddChunk(chunkCapacity);
		}

		void* Malloc(size_t size)
		{
			if (chunkHeader->size+size>chunkHeader->capacity)
			{
				AddChunk(chunkHeader->capacity>size?chunkHeader->capacity:size);
			}
			char* result=(char*)(chunkHeader+1)+chunkHeader->size;
			chunkHeader->size+=size;
			return result;
		}

		void* Realloc(void* destPtr,size_t destSize, size_t newSize)
		{
			if (destSize>=newSize)
			{
				return destPtr;
			}
			void* result=Malloc(newSize);
			return memcpy(result,destPtr,destSize);
		}

		size_t Capacity()
		{
			size_t capacity=0;
			for (ChunkHeader* item=chunkHeader;item!=NULL;item=item->next)
			{
				capacity+=item->capacity;
			}
			return capacity;
		}

		size_t Size()
		{
			size_t size=0;
			for (ChunkHeader* item=chunkHeader;item!=NULL;item=item->next)
			{
				size+=item->size;
			}
			return size;
		}

		void Clear()
		{
			while (chunkHeader!=NULL)
			{
				ChunkHeader* next=chunkHeader->next;
				allocator->Free(chunkHeader);
				chunkHeader=next;
			}
		}

		~MemoryPoolAllocator()
		{
			Clear();
			delete allocator;
		}
	private:
		void AddChunk(size_t capacity)
		{
			ChunkHeader* chunk=(ChunkHeader*)allocator->Malloc(sizeof(ChunkHeader)+capacity);
			chunk->capacity=capacity;
			chunk->size=0;
			chunk->next=chunkHeader;
			chunkHeader=chunk;
		}

		struct ChunkHeader 
		{
			size_t capacity;
			size_t size;
			ChunkHeader* next;
		};
		ChunkHeader* chunkHeader;
		size_t chunkCapacity;
		BaseAllocator* allocator;
	};

}
#endif