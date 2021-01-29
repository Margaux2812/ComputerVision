
<!-- PROJECT LOGO -->
<br />
<p align="center">

<h3 align="center">Computer Vision</h3>
<p style="font-style: italic" align="center">Sobel Filter & Binary Morphology: Erosion and Dilation</p>

<!-- TABLE OF CONTENTS -->
<details open="open">
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->

## About The Project

Project done during an Erasmus Semester in Pavia, Italy.
As part of the class "Computer Vision" of Professor Luca Lombardi, at the University of Pavia, the
main topic was first to implement a simple algorithm of computer vision in a standart computer language
such as C++ in my case. A more complex algorithm was also needed, and the program had to be a
command lin e script with optionnal parameters.

### Built With

Major frameworks I used in this project.

* [OpenCV](https://opencv.org/)

<!-- GETTING STARTED -->

## Getting Started

### Prerequisites

1. Install OpenCV
   ```sh
   sudo apt install python3-opencv
   ```

### Installation

1. Clone the repo
   ```sh
   git clone https://github.com/Margaux2812/ComputerVision.git
   ```

## Run

1. To compile the project
   ```sh
   g++ main.cpp -o main -std=c++11 `pkg-config --cflags --libs opencv`
   ```

2. To compile the project
   ```sh
   ./main image/punto.jpg [PARAM] [POWER]
   ```
As you can see, the program has multiple parameters.

### Sobel Filter

	The name of the parameter is ```sh sobel```

### Erosion

### Dilation

<!-- CONTACT -->

## Contact

Margaux VAILLANT - margauxvllt@gmail.com