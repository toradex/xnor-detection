# XNOR.ai and Toradex demo

The present demo streams video from a camera, gets each frame (as a QVideoFrame in YUV format but easily portable to a uchar pointer to the start od the frame data buffer) and generates random rectangles (x, y, width and height) with a random label, confidence and class_id. In the frontend, these rectangles are drew with its characteristics.

Redmine demo ticket: [Demo: XNOR.ai](http://redmine.toradex.int/issues/43244)

# How to use the demo

## Hardware

*Module*
  - [Apalis iMX8QM V1.0A](https://developer.toradex.com/products/apalis-som-family/modules/apalis-imx8)

*Carrier Board*
  - [Ixora V1.1A](https://developer.toradex.com/products/ixora-carrier-board)

*Additional materials required* 
  - Webcam (for now; soon will be replaced with CSI Camera Module V1.0Z)
  - HDMI monitor

## Software

- Prepare the module with a Boot2Qt image.

- Install on the module the [libatomic library](/tools) required to run the binary license tool.

- Run the [binary license tool](/tools) on the exact SoM hardware that you want to run the demo.

	- Send the result output to XNOR.ai and request an updated xnor library.

- Compile the source-code. Make sure that INCLUDEPATH in .pro is correct.

- Add the libxnorai-fast-person-detector.so to /usr/lib in Apalis iMX8.

- Add the [max_cpu.sh](http://gitlab.toradex.int/demos/xnor-detection/blob/master/max_cpu.sh) script to the Apalis iMX8 and make it run on startup.

- Deploy the compiled demo to Apalis iMX8.

## XNOR.ai contact information

- Jeff Zhu (jeff@xnor.ai) - main technical point of contact.

- Carlo C del Mundo (carlo@xnor.ai) - first contact.

# Developer Information

- The FrameGrabber class is a filter available to the frontend (in QML). 
- Each frame is will be passed to XNOR C++ class in FilterRunnable class (run method). 
- The FilterResult class has the attributes to hold lists of parameters calculated that point to the detected objects (x, y, width, height, label, class_id and confidence). For now are being generated randomly 

# ToDo

- [ ] Create a TEZI image with both libatomic and the license tool already included.
- [ ] Add the compiled Qt application to the image, dinamically linked to the XNOR.ai library.
- [ ] Create aiutomatic means to update the library once provided by XNOR.ai.
