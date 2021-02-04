
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

The name of the parameter is <i>sobel</i>

The operator uses two 3×3 kernels which are convolved with the original image to calculate approximations of the derivatives – one for horizontal changes, and one for vertical. If we define A as the source image, and Gx and Gy are two images which at each point contain the horizontal and vertical derivative approximations respectively, the computations are as follows:

<table>
  <tr>
    <td rowspan="4">Gx = </td>
  </tr>
  <tr>
    <td>+1</td>
    <td>0</td>
    <td>-1</td>
    <td rowspan="3"> * A </td>
  </tr>
  <tr>
    <td>+2</td>
    <td>0</td>
    <td>-2</td>
  </tr>
  <tr>
    <td>+1</td>
    <td>0</td>
    <td>-1</td>
  </tr>
</table>

and

<table>
  <tr>
    <td rowspan="5">Gy = </td>
  </tr>
  <tr>
    <td>+1</td>
    <td>+2</td>
    <td>+1</td>
    <td rowspan="3"> * A </td>
  </tr>
  <tr>
    <td>0</td>
    <td>0</td>
    <td>0</td>
  </tr>
  <tr>
    <td>-1</td>
    <td>-2</td>
    <td>-1</td>
  </tr>
</table>

The x-coordinate is defined here as increasing in the "right"-direction, and the y-coordinate is defined as increasing in the "down"-direction. At each point in the image, the resulting gradient approximations can be combined to give the gradient magnitude, using: 
<img src="https://render.githubusercontent.com/render/math?math=G = \sqrt{G_{x}^{2} %2B G_{y}^{2}}"> or <img src="https://render.githubusercontent.com/render/math?math=G = \mid G_{x}\mid  %2B \mid G_{y}\mid }">

### Erosion

### Dilation

<!-- CONTACT -->

## Contact

Margaux VAILLANT - margauxvllt@gmail.com