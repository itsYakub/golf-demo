<h1 align="center">
    <p>Golf Demo ⛳</p>
</h1>

<h4 align="center">
    <img src="https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white">
    <img src="https://img.shields.io/badge/CMake-%23008FBA.svg?style=for-the-badge&logo=cmake&logoColor=white">
    <img src="https://img.shields.io/badge/Visual%20Studio%20Code-0078d7.svg?style=for-the-badge&logo=visual-studio-code&logoColor=white">
<h4>

<h2 align="left"> What's going on ❓ </h2>
    <p>
    This project is a small golf demo created using <a href="https://github.com/RobLoach/raylib-cpp.git">raylib-cpp</a>. It supports the basic collision detection and other pretty basic behaviours expected from the 2D golf game.
    </p>

<h2 align=left> Prerequesites 📄 </h2>
    <ul>
        <li>raylib-cpp: <a href="https://github.com/RobLoach/raylib-cpp">https://github.com/RobLoach/raylib-cpp</a>.</li>
        <li>CMake: <a href="https://cmake.org/">https://cmake.org/</a>.</li>
        <li>GNU Makefile: <a href="https://www.gnu.org/software/make/#download">https://www.gnu.org/software/make/#download</a> (it should come automatically if you're using GCC, so the donwload shouldn't be necessary in this case).</li>
    </ul>

<h2 align="left"> Instalation 🖥️ </h2>

- Clone this repository: 
```bash
https://github.com/itsYakub/golf-demo.git --depth=1
```

- Go to the main project's directory:
```bash
cd golf-demo
```

- Create new build directory:
```bash
mkdir build
```

- Go to the build direcotry:
```bash
cd build
```

- Run the CMake command:
```bash
cmake .. -G Unix Makefiles
```

- Compile the project using GNU Make:
```bash
make
```

- Run the generated executable:
```bash
./golf
```

<h2 align="left"> LICENCE ❗ </h2>
    <p> This project is under the <a href="https://github.com/itsYakub/golf-demo/LICENCE">MIT Licence</a></p>