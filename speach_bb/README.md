# Let the robot speak 

First of all we need a software interface to convert text to speech on the speakers. For this we need ***a Text To Speech engine**. The TTS engine is used here is **eSpeak**.  The voice may be a little robotic, however it runs offline.

1. First let’s test if the audio is working on the Raspberry Pi (or any other PCs).  Run the following command:

```hash
aplay /usr/share/sounds/alsa/*
```

> If you are able to hear the sounds like “Front Center”,”Front Left”, “Front Right” and so on, your sound is working!  

2. Next, install **eSpeak**.  Run the following in terminal to install espeak:

```bash
sudo apt-get install espeak
```

3. Get the Raspberry Pi Speaking from the Command Line

After eSpeak has been successfully installed on the Raspberry Pi, run the following command to test eSpeak:

```bash
espeak "Hello World" 2>/dev/null
```

You should hear “Hello World” from the speakers.  Your Raspberry Pi is speaking!