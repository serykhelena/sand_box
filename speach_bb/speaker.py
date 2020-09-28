import logging 

import pyttsx3


logging.basicConfig(level=logging.DEBUG, format='%(asctime)s - %(name)s - %(levelname)s - %(message)s')
logger = logging.getLogger(__name__)

class Speaker:
    def __init__(self):
        self.tts = pyttsx3.init()  # initialization of speach engine 
        self.voices = self.tts.getProperty('voices')
        
        # Default configuration
        self.tts.setProperty('voice', 'english')
        self.tts.setProperty('rate', 150)
        self.tts.setProperty('volume', 0.8)


    def say(self, msg):
        self.tts.say(msg)
        self.tts.runAndWait()


    def show_all_voices(self):
        for voice in self.voices:
            print(f'>>>>>>>', 
                  f'Name: {voice.name}', 
                  f'ID: {voice.id}',
                  f'Language(s): {voice.languages}',
                  f'Gender: {voice.gender}',
                  f'Age: {voice.age}'
                  )


    def change_voice(self, voice_name):
        flag = False 
        for voice in self.voices:
            if voice.name == voice_name:
                self.tts.setProperty('voice', voice.id)
                logger.debug(f"Voice {voice_name} was changed to  successfully!")
                flag = True 
                break 
        if not flag:
            logger.debug(f"Voice {voice_name} not found. Changing - faild!")
        

    def change_rate(self, new_rate): 
        # rate in %, >100 
        self.tts.setProperty('rate', new_rate)


    def __str__(self):
        return f"Hi, I'm a Speaker!"




if __name__ == '__main__':
    test = Speaker()
    test.show_all_voices()
    test.say('I am the danger')

