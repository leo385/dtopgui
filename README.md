# dtopgui - Open source code!
Create network topology and simulate it in real time

This software is still building, so if you have any advices for me, contact me private on my github email.

# Requirments
 <ul>
 <li>MSBUILD (from Visual Studio Installer)</li>
 <li>Microsoft visual c++ redistributable 2015-2022 version</li>
 <li>DirectX11</li>
 <li>Graphic's driver</li>
</ul>

# Introduction
In the beginning i'd like to mention that i've used "javidx9" graphic's library called "olcPixelGameEngine".
<br><br>Source of the library:
`https://github.com/OneLoneCoder/olcPixelGameEngine`

This Application allows you to create really basic network topology.
I'm developing this program, because I think this software may help you with understanding networks.
The devices haven't specified type, <b>In toolbar you have</b>:

## Devices to connect among
`ROUTER`
`SWITCH`
`SERVER`
`PC`
`LAPTOP`

## Three type of Shapes to draw for clear looking on the topology
`Rectangle`
`Triangle`
`Circle`

## Eight type of media
`Straight-Through`
`Cross-Over`
`Fiber-Optic`
`Serial-DCE`
`Serial-DTE`
`Console`
`USB`

## I Added Rubber too, to erasing objects.
`Eraser`

# Building repository
I prefered to use `MSBUILD` instead of `MAKE` to build the repository.<br>
Before building that project you should clone him into "your own" directory
<br>
<pre><code>git clone https://github.com/leo385/dtopgui.git</code></pre>

After cloning process, you can build the project being in ``/dtopgui`` folder.
<br><b>All you have to do is typing the command below:</b></br>
<pre><code>msbuild -property:Configuration=Release build/dtopgui.vcxproj</code></pre>

After building, you can start the program that is located in ``/Release`` folder,
just run <b>dtopgui.exe</b>.


