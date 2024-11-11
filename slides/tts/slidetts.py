import os
from gtts import gTTS

def text_files_to_mp3():
    # Iterate over all text files in the current directory
    for filename in os.listdir('.'):
        if filename.lower().endswith('.txt'):
            # Read the text file content
            with open(filename, 'r', encoding='utf-8') as file:
                text = file.read()

            # Generate the MP3 filename
            mp3_filename = f"{os.path.splitext(filename)[0]}.mp3"

            # Convert text to speech
            tts = gTTS(text=text, lang='en', slow=False)
            tts.save(mp3_filename)
            print(f"Generated {mp3_filename}")

if __name__ == "__main__":
    text_files_to_mp3()
