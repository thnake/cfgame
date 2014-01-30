#include "audioplayer.h"
#include <QAudioFormat>
#include <QAudioOutput>
#include <QFile>



AudioPlayer::AudioPlayer()
{
}


void AudioPlayer::Play()
{
/*
    float pcm[];
    QAudioFormat  format;
    format.setFrequency(8000);
    format.setChannels(1);
    format.setSampleSize(8);
    format.setCodec("audio/pcm");      // PCM, sollte immer gehen
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::UnSignedInt);
    QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());
    //if (!info.isFormatSupported(format)) … // Fehlerbehandlung

    QFile  inputFile; // class member .
    inputFile.setFileName("O:/…");
    inputFile.open(QIODevice::ReadOnly);
    QAudioOutput* audio  = new QAudioOutput(format);

    audio->start(&inputFile);
*/
}
