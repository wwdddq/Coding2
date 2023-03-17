# Coding2 Final Project
The project I did was to use OpenFrameWork to create audio visualisations. I was interested in audio visualisation during my coding1 studies at school, but at the time I didn't know much about how to do projects in this area in js, so I ended up giving up. This time, in the process of learning OF, I found that OF has instructions to extract the spectrum of audio directly, which is very helpful for doing audio visualisation, so I chose to do this topic. In terms of presentation, because I am more interested in 2D and because I wanted to experiment more with the features of OF, I chose to do this assignment in different forms of segmentation for the motion effects, and the method of segmentation was to extract audio keyframes. I also learnt a lot during this time and knew a lot of code instructions that I hadn't seen before, which I believe will be useful for my future creative coding studies. All in all, I'm just fine with OF being a great tool, probably because it was easier for me than I thought it would be with the foundation of the first semester.

## To watch the full video click on:

### Here are some of the techniques and screenshots I used.


- status 1 Very simple animation using ofTranslate in combination with FFT to control the screen centre point change.

<img width="1649" alt="截屏2023-03-17 12 21 47" src="https://user-images.githubusercontent.com/119059058/225903890-ee96e220-fd06-44a0-9a42-484efcf88e85.png">

- Status 2 calculated the position of each point on the circle using trigonometric functions. By continuously calculating the position of the target point, parameters such as the length, position and size of each point were updated, resulting in an animation with audio feedback.

<img width="1645" alt="截屏2023-03-17 12 22 47" src="https://user-images.githubusercontent.com/119059058/225903931-54304e69-f803-44a8-b183-2bb3353a9a4a.png">

- Status 3 uses sine-wave animations generated from an adaptation of Zach Lieberman's sine wave.

<img width="1647" alt="截屏2023-03-17 12 22 19" src="https://user-images.githubusercontent.com/119059058/225903914-5e7b7f09-0694-4d13-b798-cfcfe65b9781.png">

- Status 4 uses two sets of circles to visualise the audio. The size of the larger circle depends on the FFT value. The circles are generated using a random number generator with a fixed seed value, so that the circles appear in the same position in each frame. This creates a static background where the circles expand and contract with the music. The radius of the smaller circles is fixed and does not change size with the FFT value. These circles are drawn on top of the larger circles to create a dynamic foreground. The smaller circles move randomly and are drawn at different positions in each frame, so they appear to move with the music.

<img width="1645" alt="截屏2023-03-17 12 23 35" src="https://user-images.githubusercontent.com/119059058/225904041-b7f6b394-009e-4731-b220-9e376be7087d.png">

- Status 5 implements a noise-based audio visualisation, using ofIcoSpherePrimitive to create a 4-level Icosphere and calculating the noise value for each vertex using the ofNoise() function. The position of the vertices is then adjusted according to the noise value so that it changes in response to the audio. But in fact, the function about mesh is not yet mastered very well and the desired effect cannot be achieved, so we need to continue to go deeper.

<img width="1647" alt="截屏2023-03-17 12 24 25" src="https://user-images.githubusercontent.com/119059058/225904125-a37b1f0d-84d0-42b2-9911-eef8e5e31e06.png">

- Status 6 uses noise and spectral data to generate a dynamic line visualisation. I first created a set of basic vertices within a rectangle via a for loop and then set the colour of each vertex to a gradient colour based on its y-coordinate value. Next, a nested loop was used to iterate over the trajectory at each base position to generate a set of paths made up of lines. During this trajectory generation process, the direction and amplitude of the lines are calculated based on noise and audio spectrum data, and then new points are added to the current trajectory. Finally, all trajectories are rendered to the screen, creating a dynamic audio visualisation. However, there are problems running this code, the details of which I have written in the comments.

<img width="1649" alt="截屏2023-03-17 12 24 46" src="https://user-images.githubusercontent.com/119059058/225904173-64f14874-33a8-466e-92b3-9cad5d6d8087.png">


### References
https://junkiyoshi.com/openframeworks20221126/
https://www.youtube.com/watch?v=5N12MPK1aC4&list=PL6QF0yo3Zj7DbN76C5-_6VCDF5CPBIz6l&index=11
https://www.youtube.com/watch?v=kYejiSrzFzs&list=PL6QF0yo3Zj7DbN76C5-_6VCDF5CPBIz6l&index=11
https://github.com/GuanghanWu/CodingTwo_FinalProject/blob/main/codingTwoFinal/src/ofApp.cpp
https://openframeworks.cc//documentation/sound/ofSoundPlayer/#!show_ofSoundGetSpectrum
https://en.wikipedia.org/wiki/Fast_Fourier_transform

### Audio 
https://orangefreesounds.com/energetic-dreamy-electronic-music/








