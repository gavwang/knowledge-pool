package com.gavinw.android.media;

import android.media.MediaCodec;
import android.media.MediaCodecInfo;
import android.media.MediaCodecList;
import android.media.MediaFormat;

import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.ShortBuffer;

public class CodecDemo {

    short [] getSampleForChannel (MediaCodec codec, int bufferID, int channelIX)
    {
        ByteBuffer outputBuffer = codec.getOutputBuffer(bufferID);

        MediaFormat format = codec.getOutputFormat();

        ShortBuffer samples = outputBuffer.order(ByteOrder.nativeOrder()).asShortBuffer();

        int numChannels = format.getInteger(MediaFormat.KEY_CHANNEL_COUNT);
        if (channelIX  < 0 || channelIX >= numChannels)
            return  null;

        short [] res = new short[samples.remaining()/numChannels];

        for(int i = 0; i < res.length ; i++)
        {
            res[i] = samples.get(i*numChannels + channelIX);
        }

        return  res;
    }


    /**
     * create media codec by name
     *
     */
    MediaCodec createCodecByName(String name){
        MediaCodecList mediaCodecList = new MediaCodecList(MediaCodecList.REGULAR_CODECS);
        mediaCodecList.findDecoderForFormat(MediaFormat.createVideoFormat(MediaFormat.MIMETYPE_VIDEO_HEVC,1280,720));
        mediaCodecList.findEncoderForFormat(MediaFormat.createVideoFormat(MediaFormat.MIMETYPE_VIDEO_HEVC,1280,720));

        try {
            MediaCodec codec = MediaCodec.createByCodecName(MediaFormat.MIMETYPE_VIDEO_HEVC);
            return  codec;
        } catch (IOException e) {
            e.printStackTrace();
        }

        return  null;
    }

    static MediaCodecInfo selectCodec(String type){
        int num = MediaCodecList.getCodecCount();

        MediaCodecList mediaCodecList = new MediaCodecList(MediaCodecList.ALL_CODECS);
        MediaCodecInfo[] infos = mediaCodecList.getCodecInfos();
        for (MediaCodecInfo info: infos) {
            String[] types = info.getSupportedTypes();
            for (String t: types ) {
                if (t.equalsIgnoreCase(type))
                    return  info;
            }

        }

        return  null;
    }

    void AvcEncoder(int width, int height, int framerate, int bitrate){
        MediaFormat format = MediaFormat.createVideoFormat(MediaFormat.MIMETYPE_VIDEO_AVC, width, height);


        try {
            MediaCodec codec = MediaCodec.createByCodecName(MediaFormat.MIMETYPE_VIDEO_AVC);

            codec.configure(format, null,null, MediaCodec.CONFIGURE_FLAG_ENCODE);
        }catch (IOException e){

        }

    }
}
