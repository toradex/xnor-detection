# XNOR.ai and Toradex Sample

The present sample streams video from a camera, gets each frame (as a QVideoFrame
in YUV format but easily portable to a uchar pointer to the start od the frame
data buffer) and runs the XNOR.ai inference engine to get person detection
coordinates, taking this result to generate rectangles (x, y, width and height)
with labels, confidence and class_id. In the frontend, these rectangles are drew
with its characteristics.

This sample uses the Boot2Qt image available in Qt for Device Creation from
The Qt Company. If you want to use it for commercial purposes, make sure to
comply to The Qt Company licensing.

[![Edge AI with XNOR.ai and Toradex Apalis iMX8](http://img.youtube.com/vi/epWmEXY63F0/0.jpg)](http://www.youtube.com/watch?v=epWmEXY63F0)

# How to use the sample

## Hardware

*Module*
  - [Apalis iMX8QM V1.0A](https://developer.toradex.com/products/apalis-som-family/modules/apalis-imx8)

*Carrier Board*
  - [Ixora V1.1A](https://developer.toradex.com/products/ixora-carrier-board)

*Additional materials required* 
  - Webcams - tested with up to 3 cameras
  - HDMI monitor

## Software

- Prepare the module with a Boot2Qt image.

- Install on the module the [libatomic library](/tools) required to run the
binary license tool.

- Run the [binary license tool](/tools) on the exact SoM hardware that you want
to run the demo.

	- Send the result output to XNOR.ai and request an updated xnor library.

- Compile the source-code. Make sure that INCLUDEPATH in .pro is correct.

- Add the libxnorai-fast-person-detector.so to /usr/lib in Apalis iMX8.

- Add the [xnor_demo_run.sh](/tools) script to the Apalis iMX8 and make it run
on startup.

- Deploy the compiled demo to Apalis iMX8.

## XNOR.ai contact information

[XNOR.ai partner page on Toradex website](https://www.toradex.com/support/partner-network/services/100008/xnorai).

# Developer Information

- The FrameGrabber class is a filter available to the frontend (in QML). 
- Each frame is passed to XNOR C++ class in FilterRunnable class (run method).
- The FilterResult class has the attributes to hold lists of parameters
calculated that point to the detected objects (x, y, width, height, label,
class_id and confidence).

# ToDo

- [ ] Create a TEZI image with both libatomic and the license tool already
included.
- [ ] Add the compiled Qt application to the image, dynamically linked to the
XNOR.ai library.
- [ ] Create automatic means to update the library once provided by XNOR.ai.
