<div align="center">
 
 <picture>
   <img src="assets/textures/snake.png" width="20%" style="border: none; box-shadow: none;" alt="Suzzie Snake"/>
 </picture>
 
 <h1>
   Suzzie Snake
   <br/>
   <sub>Simple C++ snake game 🕹️</sub>
 </h1>

 <br/>

 <p align="center">
   <img src="https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white" />
   <img src="https://img.shields.io/badge/SFML-8CC445?style=for-the-badge&logo=c%2B%2B&logoColor=white" />
   <img src="https://img.shields.io/badge/Visual%20Studio-5C2D91.svg?style=for-the-badge&logo=visual-studio&logoColor=white" />
   <img src="https://img.shields.io/badge/Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white" />
 </p>
</div>

# Overview

Suzzie Snake is a classic arcade game built entirely in C++ using the modern **SFML 3** multimedia library.

## Getting Started

Choose the path that suits your needs: simply play the game or build it from the source code.

### 🎮 For Gamers

You don't need to compile anything or install extra software.

1. Go to the [Releases](../../releases) section of this repository.
2. Download the latest `.zip` archive.
3. Extract the folder to your computer.
4. Run `SuzzieSnake.exe` and enjoy!

### 🛠️ For Developers
To get a local copy up and running, follow these steps. The project is pre-configured for **Visual Studio** (C++20).

#### Prerequisites
* **Visual Studio** (or any C++20 compatible compiler)
* **SFML 3.0.2** (Visual C++ version) - [Download Here](https://www.sfml-dev.org/download/sfml/3.0.2/)

#### Installation

1.  **Clone the repository**
    ```sh
    git clone https://github.com/Lesykkk/SuzzieSnake.git
    cd SuzzieSnake
    ```

2.  **Set up the SFML Library**
    * Extract your downloaded SFML 3.0.2 archive.
    * Move the extracted folder into the `Libraries/` directory at the root of the project.
    > **❗❗❗ Important:** You **MUST** rename this folder exactly to `SFML`.

    *Your folder structure should look exactly like this:*
    ```text
    \Libraries
              \SFML
                    \bin
                    \include
                    \lib
                    ...
    ```

3.  **Build and run the application**
    * Open the solution file (`.sln`) in Visual Studio.
    * Set your build configuration to **Release** (or Debug).
    * Click **Build Solution** and then click **Run**.
    > **Note:** All required `.dll` will be automatically copied to your output directory.

## Usage

Here are the main ways to interact with the game:

1.  **Gameplay**: Use `W A S D` or `Arrow Keys` to control the snake. Eat apples to grow, and don't hit the walls or your own tail.
2.  **Navigation**: Use the Mouse or Keyboard (`Up`/`Down` + `Enter`/`Esc`) to seamlessly navigate the menus.

## Contributing

If you have a suggestion that would make this project better, please fork the repo and create a pull request.
Don't forget to give the project a star! Thanks again!

1.  Fork the Project
2.  Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3.  Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4.  Push to the Branch (`git push origin feature/AmazingFeature`)
5.  Open a Pull Request

## License

Distributed under the MIT License. See [LICENSE](./LICENSE) for more information.

## Contacts

Project Link: https://github.com/Lesykkk/SuzzieSnake
