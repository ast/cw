# CW (morse code)

This is a program in C that generates perfectly timed Morse code on your sound card. The keying waveform is low pass filtered to remove keying clicks. The speed (wpm), pitch and rise time of the keying waveform are configureable.

There are many morse code programs out there but I have have always found them to be lacking in one way or another. It seems many of them have been written by people that has never used morse code to communicate. There are many misconceptions of how morse code works. When using morse code at a useful speed, the operator no longer thinks of the codes as long or short but rather as little "sounds" or "melodies", and he/she has developed a reflex to associate the sound with a symbol. I have found "[The Art and Skill of Radio-Telegraphy](http://www.tasrt.ca/TASRTVersions/TASRT.pdf) to be the best resource for anyone that wants to learn more about radio telegraphy.


## Getting Started

**This program is work under progress.**

I'm writing this program primarily to use as a kind of morse code front end for a ham radio repeater I'm implementing in Erlang but you are free to use it in your own programs.

Right now I've only implemented the actual audio code on Mac OSX. But I'm planning an ALSA version in a not to distant future. Since it doesn't relay on any "delays" it would also be trivial to write to a sound file instead of real-time audio. I believe this could be quite fast as the DSP code is very straight forward and efficient.

### Prerequisites

Right now you need Xcode to build. I will create a `Makefile` soon.

### Installing and running

Just build and run in Xcode. Then go play with the code. 

## Contributing

Ideas are also welcome! I would be happy to merge any relevant patches.


## Authors

* **Albin Stigö** - *Initial work* - [albinstigo.me](http://albinstigo.me)

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* The ring buffer code was inspired by [Juho Snellman](https://www.snellman.net/blog/archive/2016-12-13-ring-buffers/)
* The DSP code was inspired by [The Scientist and Engineer's Guide to Digital Signal Processing](http://www.dspguide.com), an amazing book!
