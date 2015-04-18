BallGame Readme

Well this is the 5th iteration of BallGame I think..
I got it kind of working until I decided to port it to SDL2.
It will compile and run on Linux (Arch) but is buggy as hell
on my desktop the physics are even more broken (Unwanted extra features)
then before.

Brock York

Building for Wandoze(Windows):

TLDR;
1. Download this premade zip I created:
2. Extract code:blocks zip and run code blocks
3. Follow get the source step
4. Build source and run
5. ???
6. Profit from OSS knowledge


1.Get a copy of Code:Blocks for windows which includes the Mingw cross compiler.
AKA:http://sourceforge.net/projects/codeblocks/files/Binaries/13.12/Windows/codeblocks-13.12mingw-setup.exe
2.Install code:blocks
3.When first booting code:blocks it will ask you for which compiler you want to use select GCC.

Getting SDL2
1. Download & extract the SDL2 development tar archive(You'll need 7zip or something to extract tar.gz): https://www.libsdl.org/release/SDL2-devel-2.0.3-mingw.tar.gz
2. From the SDL2.0.3 directory that was just extracted there is a i686-w64-mingw64 directory
3. Copy the folders (bin,include,lib,share) from inside the i686-w64-mingw6 to C:\Program Files (x86)\CodeBlocks\MinGW\
4. Download https://hg.libsdl.org/SDL/raw-file/e217ed463f25/include/SDL_platform.h and copy it to C:\Program Files (x86)\CodeBlocks\MinGW\include\SDL2\ replacing the current on there
because it has a bug dammit!

Getting SDL2_ttf
1. Download & extract SDL2_ttf tar archive https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-devel-2.0.12-mingw.tar.gz
2.Copy bin, include and lib folders from SDL2_ttf-2.0.12\i686-w64-mingw32 you just extracted to C:\Program Files (x86)\CodeBlocks\MinGW

Getting SDL2_image
1. Download & extract SDL2_image tar archive https://www.libsdl.org/projects/SDL_image/release/SDL2_image-devel-2.0.0-mingw.tar.gz
2.Copy bin, include and lib folders from SDL2_image-2.0.0\i686-w64-mingw32 you just extracted to C:\Program Files (x86)\CodeBlocks\MinGW\ 


Getting Boost library
1.Download & extract http://downloads.sourceforge.net/project/boost/boost/1.58.0/boost_1_58_0.zip?r=http%3A%2F%2Fsourceforge.net%2Fprojects%2Fboost%2Ffiles%2Fboost%2F1.58.0%2F&ts=1429329669&use_mirror=internode
2. Copy boost_1_58_0\boost directory to C:\Program Files (x86)\CodeBlocks\MinGW\include
3. You should now have a C:\Program Files (x86)\CodeBlocks\MinGW\include\boost directory filled with the boost headers


Getting the source
1. Install git-bash https://github.com/msysgit/msysgit/releases/download/Git-1.9.5-preview20150319/Git-1.9.5-preview20150319.exe
2. Open git-bash by double clicking on the git-bash icon
3. clone source git clone https://github.com/yaspoon/BallGame.git

Building
1. Go into BallGame directory and open BallGame.cbp
2. Press F9 to build and run or goto build->run at the top menu



