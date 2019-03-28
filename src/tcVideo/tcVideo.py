#!/usr/bin/python

import vapoursynth as vs
import mvsfunc as mvf
import math

class tcVideo:
    def __init__(self, fileName, **kargs):
        self.core = vs.core
        self.clip = self.core.lsmas.LWLibavSource(fileName, **kargs)
        self.clip = mvf.ToRGB(self.clip, depth=8, dither=6, useZ=True)
    
    def tcVideoGetProps(self):
        frameCount = self.clip.num_frames
        width = self.clip.width
        height = self.clip.height

        return (frameCount, width, height)
    
    def tcVideoSetRes(self, width, height):
        self.clip = self.core.resize.Bicubic(self.clip, width, height)

        return 0
    
    def tcVideoGetFrame(self, frameNumber):
        frame = self.clip.get_frame(frameNumber)
        plane0 = frame.get_read_array(0)
        plane1 = frame.get_read_array(1)
        plane2 = frame.get_read_array(2)
        return (plane0, plane1, plane2)
    
    def tcVideoGetFrameByTime(self, frameTime):
        #frameTime is millisecond
        frameNumber = frameTime * self.clip.fps_num / (self.clip.fps_den * 1000)
        frameNumber = math.ceil(frameNumber)

        return self.tcVideoGetFrame(frameNumber)
    