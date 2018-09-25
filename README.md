# XNOR.ai and Toradex demo

The present demo streams video from a camera, gets each frame (as a QVideoFrame in YUV format but easily portable to a uchar pointer to the start od the frame data buffer) and generates random rectangles (x, y, width and height) with a random label, confidence and class_id. In the frontend, these rectangles are drew with its characteristics.

# How to use the demo
*Module*
  - [Apalis iMX8QM V1.0A](https://developer.toradex.com/products/apalis-som-family/modules/apalis-imx8)

*Carrier Board*
  - [Ixora V1.1A](https://developer.toradex.com/products/ixora-carrier-board)

*Additional materials required* 
  - Webcam (for now; soon will be replaced with CSI Camera Module V1.0Z)
  - HDMI monitor

# Developer Information

- The FrameGrabber class is a filter available to the frontend (in QML). 
- Each frame is will be passed to XNOR C++ class in FilterRunnable class (run method). 
- The FilterResult class has the attributes to hold lists of parameters calculated that point to the detected objects (x, y, width, height, label, class_id and confidence). For now are being generated randomly 
