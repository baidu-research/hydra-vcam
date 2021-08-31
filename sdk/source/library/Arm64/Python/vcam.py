# This file was automatically generated by SWIG (http://www.swig.org).
# Version 3.0.12
#
# Do not make changes to this file unless you know what you are doing--modify
# the SWIG interface file instead.

from sys import version_info as _swig_python_version_info
if _swig_python_version_info >= (2, 7, 0):
    def swig_import_helper():
        import importlib
        pkg = __name__.rpartition('.')[0]
        mname = '.'.join((pkg, '_vcam')).lstrip('.')
        try:
            return importlib.import_module(mname)
        except ImportError:
            return importlib.import_module('_vcam')
    _vcam = swig_import_helper()
    del swig_import_helper
elif _swig_python_version_info >= (2, 6, 0):
    def swig_import_helper():
        from os.path import dirname
        import imp
        fp = None
        try:
            fp, pathname, description = imp.find_module('_vcam', [dirname(__file__)])
        except ImportError:
            import _vcam
            return _vcam
        try:
            _mod = imp.load_module('_vcam', fp, pathname, description)
        finally:
            if fp is not None:
                fp.close()
        return _mod
    _vcam = swig_import_helper()
    del swig_import_helper
else:
    import _vcam
del _swig_python_version_info

try:
    _swig_property = property
except NameError:
    pass  # Python < 2.2 doesn't have 'property'.

try:
    import builtins as __builtin__
except ImportError:
    import __builtin__

def _swig_setattr_nondynamic(self, class_type, name, value, static=1):
    if (name == "thisown"):
        return self.this.own(value)
    if (name == "this"):
        if type(value).__name__ == 'SwigPyObject':
            self.__dict__[name] = value
            return
    method = class_type.__swig_setmethods__.get(name, None)
    if method:
        return method(self, value)
    if (not static):
        if _newclass:
            object.__setattr__(self, name, value)
        else:
            self.__dict__[name] = value
    else:
        raise AttributeError("You cannot add attributes to %s" % self)


def _swig_setattr(self, class_type, name, value):
    return _swig_setattr_nondynamic(self, class_type, name, value, 0)


def _swig_getattr(self, class_type, name):
    if (name == "thisown"):
        return self.this.own()
    method = class_type.__swig_getmethods__.get(name, None)
    if method:
        return method(self)
    raise AttributeError("'%s' object has no attribute '%s'" % (class_type.__name__, name))


def _swig_repr(self):
    try:
        strthis = "proxy of " + self.this.__repr__()
    except __builtin__.Exception:
        strthis = ""
    return "<%s.%s; %s >" % (self.__class__.__module__, self.__class__.__name__, strthis,)

try:
    _object = object
    _newclass = 1
except __builtin__.Exception:
    class _object:
        pass
    _newclass = 0

YUV420p = _vcam.YUV420p
RAW14 = _vcam.RAW14
H26X = _vcam.H26X
JPEG = _vcam.JPEG
METEDATA = _vcam.METEDATA
MONO = _vcam.MONO
DEPTH = _vcam.DEPTH
OUTPUT_INDEX_SIZE = _vcam.OUTPUT_INDEX_SIZE
USB_SUCCESS = _vcam.USB_SUCCESS
USB_ERROR_IO = _vcam.USB_ERROR_IO
USB_ERROR_INVALID_PARAM = _vcam.USB_ERROR_INVALID_PARAM
USB_ERROR_ACCESS = _vcam.USB_ERROR_ACCESS
USB_ERROR_NO_DEVICE = _vcam.USB_ERROR_NO_DEVICE
USB_ERROR_NOT_FOUND = _vcam.USB_ERROR_NOT_FOUND
USB_ERROR_BUSY = _vcam.USB_ERROR_BUSY
USB_ERROR_TIMEOUT = _vcam.USB_ERROR_TIMEOUT
USB_ERROR_OVERFLOW = _vcam.USB_ERROR_OVERFLOW
USB_ERROR_PIPE = _vcam.USB_ERROR_PIPE
USB_ERROR_INTERRUPTED = _vcam.USB_ERROR_INTERRUPTED
USB_ERROR_NO_MEM = _vcam.USB_ERROR_NO_MEM
USB_ERROR_NOT_SUPPORTED = _vcam.USB_ERROR_NOT_SUPPORTED
USB_ERROR_OTHER = _vcam.USB_ERROR_OTHER
IMG_FORMAT_GRAY = _vcam.IMG_FORMAT_GRAY
IMG_FORMAT_I420 = _vcam.IMG_FORMAT_I420
IMG_FORMAT_I422 = _vcam.IMG_FORMAT_I422
IMG_FORMAT_I444 = _vcam.IMG_FORMAT_I444
IMG_FORMAT_YUV444 = _vcam.IMG_FORMAT_YUV444
IMG_FORMAT_RGB = _vcam.IMG_FORMAT_RGB
IMG_FORMAT_RGB_PLANAR = _vcam.IMG_FORMAT_RGB_PLANAR
IMG_FORMAT_BGR = _vcam.IMG_FORMAT_BGR
IMG_FORMAT_BGR_PLANAR = _vcam.IMG_FORMAT_BGR_PLANAR
ENCODE_H264_MODE = _vcam.ENCODE_H264_MODE
ENCODE_H265_MODE = _vcam.ENCODE_H265_MODE
class CameraInfo(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, CameraInfo, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, CameraInfo, name)
    __repr__ = _swig_repr
    __swig_setmethods__["imageWidth"] = _vcam.CameraInfo_imageWidth_set
    __swig_getmethods__["imageWidth"] = _vcam.CameraInfo_imageWidth_get
    if _newclass:
        imageWidth = _swig_property(_vcam.CameraInfo_imageWidth_get, _vcam.CameraInfo_imageWidth_set)
    __swig_setmethods__["imageHeight"] = _vcam.CameraInfo_imageHeight_set
    __swig_getmethods__["imageHeight"] = _vcam.CameraInfo_imageHeight_get
    if _newclass:
        imageHeight = _swig_property(_vcam.CameraInfo_imageHeight_get, _vcam.CameraInfo_imageHeight_set)
    __swig_setmethods__["startX"] = _vcam.CameraInfo_startX_set
    __swig_getmethods__["startX"] = _vcam.CameraInfo_startX_get
    if _newclass:
        startX = _swig_property(_vcam.CameraInfo_startX_get, _vcam.CameraInfo_startX_set)
    __swig_setmethods__["startY"] = _vcam.CameraInfo_startY_set
    __swig_getmethods__["startY"] = _vcam.CameraInfo_startY_get
    if _newclass:
        startY = _swig_property(_vcam.CameraInfo_startY_get, _vcam.CameraInfo_startY_set)
    __swig_setmethods__["endX"] = _vcam.CameraInfo_endX_set
    __swig_getmethods__["endX"] = _vcam.CameraInfo_endX_get
    if _newclass:
        endX = _swig_property(_vcam.CameraInfo_endX_get, _vcam.CameraInfo_endX_set)
    __swig_setmethods__["endY"] = _vcam.CameraInfo_endY_set
    __swig_getmethods__["endY"] = _vcam.CameraInfo_endY_get
    if _newclass:
        endY = _swig_property(_vcam.CameraInfo_endY_get, _vcam.CameraInfo_endY_set)
    __swig_setmethods__["inputDimWidth"] = _vcam.CameraInfo_inputDimWidth_set
    __swig_getmethods__["inputDimWidth"] = _vcam.CameraInfo_inputDimWidth_get
    if _newclass:
        inputDimWidth = _swig_property(_vcam.CameraInfo_inputDimWidth_get, _vcam.CameraInfo_inputDimWidth_set)
    __swig_setmethods__["inputDimHeight"] = _vcam.CameraInfo_inputDimHeight_set
    __swig_getmethods__["inputDimHeight"] = _vcam.CameraInfo_inputDimHeight_get
    if _newclass:
        inputDimHeight = _swig_property(_vcam.CameraInfo_inputDimHeight_get, _vcam.CameraInfo_inputDimHeight_set)
    __swig_setmethods__["inputFormat"] = _vcam.CameraInfo_inputFormat_set
    __swig_getmethods__["inputFormat"] = _vcam.CameraInfo_inputFormat_get
    if _newclass:
        inputFormat = _swig_property(_vcam.CameraInfo_inputFormat_get, _vcam.CameraInfo_inputFormat_set)
    __swig_setmethods__["meanValue"] = _vcam.CameraInfo_meanValue_set
    __swig_getmethods__["meanValue"] = _vcam.CameraInfo_meanValue_get
    if _newclass:
        meanValue = _swig_property(_vcam.CameraInfo_meanValue_get, _vcam.CameraInfo_meanValue_set)
    __swig_setmethods__["stdValue"] = _vcam.CameraInfo_stdValue_set
    __swig_getmethods__["stdValue"] = _vcam.CameraInfo_stdValue_get
    if _newclass:
        stdValue = _swig_property(_vcam.CameraInfo_stdValue_get, _vcam.CameraInfo_stdValue_set)
    __swig_setmethods__["isOutputYUV"] = _vcam.CameraInfo_isOutputYUV_set
    __swig_getmethods__["isOutputYUV"] = _vcam.CameraInfo_isOutputYUV_get
    if _newclass:
        isOutputYUV = _swig_property(_vcam.CameraInfo_isOutputYUV_get, _vcam.CameraInfo_isOutputYUV_set)
    __swig_setmethods__["isOutputH26X"] = _vcam.CameraInfo_isOutputH26X_set
    __swig_getmethods__["isOutputH26X"] = _vcam.CameraInfo_isOutputH26X_get
    if _newclass:
        isOutputH26X = _swig_property(_vcam.CameraInfo_isOutputH26X_get, _vcam.CameraInfo_isOutputH26X_set)
    __swig_setmethods__["isOutputJPEG"] = _vcam.CameraInfo_isOutputJPEG_set
    __swig_getmethods__["isOutputJPEG"] = _vcam.CameraInfo_isOutputJPEG_get
    if _newclass:
        isOutputJPEG = _swig_property(_vcam.CameraInfo_isOutputJPEG_get, _vcam.CameraInfo_isOutputJPEG_set)
    __swig_setmethods__["mode"] = _vcam.CameraInfo_mode_set
    __swig_getmethods__["mode"] = _vcam.CameraInfo_mode_get
    if _newclass:
        mode = _swig_property(_vcam.CameraInfo_mode_get, _vcam.CameraInfo_mode_set)

    def __init__(self):
        this = _vcam.new_CameraInfo()
        try:
            self.this.append(this)
        except __builtin__.Exception:
            self.this = this
    __swig_destroy__ = _vcam.delete_CameraInfo
    __del__ = lambda self: None
CameraInfo_swigregister = _vcam.CameraInfo_swigregister
CameraInfo_swigregister(CameraInfo)

MAX_LABEL_SIZE = _vcam.MAX_LABEL_SIZE
MAX_EXTINPUT_SIZE = _vcam.MAX_EXTINPUT_SIZE
MAX_OBJ = _vcam.MAX_OBJ
class Network1Par(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, Network1Par, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, Network1Par, name)
    __repr__ = _swig_repr
    __swig_setmethods__["imageWidth"] = _vcam.Network1Par_imageWidth_set
    __swig_getmethods__["imageWidth"] = _vcam.Network1Par_imageWidth_get
    if _newclass:
        imageWidth = _swig_property(_vcam.Network1Par_imageWidth_get, _vcam.Network1Par_imageWidth_set)
    __swig_setmethods__["imageHeight"] = _vcam.Network1Par_imageHeight_set
    __swig_getmethods__["imageHeight"] = _vcam.Network1Par_imageHeight_get
    if _newclass:
        imageHeight = _swig_property(_vcam.Network1Par_imageHeight_get, _vcam.Network1Par_imageHeight_set)
    __swig_setmethods__["startX"] = _vcam.Network1Par_startX_set
    __swig_getmethods__["startX"] = _vcam.Network1Par_startX_get
    if _newclass:
        startX = _swig_property(_vcam.Network1Par_startX_get, _vcam.Network1Par_startX_set)
    __swig_setmethods__["startY"] = _vcam.Network1Par_startY_set
    __swig_getmethods__["startY"] = _vcam.Network1Par_startY_get
    if _newclass:
        startY = _swig_property(_vcam.Network1Par_startY_get, _vcam.Network1Par_startY_set)
    __swig_setmethods__["endX"] = _vcam.Network1Par_endX_set
    __swig_getmethods__["endX"] = _vcam.Network1Par_endX_get
    if _newclass:
        endX = _swig_property(_vcam.Network1Par_endX_get, _vcam.Network1Par_endX_set)
    __swig_setmethods__["endY"] = _vcam.Network1Par_endY_set
    __swig_getmethods__["endY"] = _vcam.Network1Par_endY_get
    if _newclass:
        endY = _swig_property(_vcam.Network1Par_endY_get, _vcam.Network1Par_endY_set)
    __swig_setmethods__["inputDimWidth"] = _vcam.Network1Par_inputDimWidth_set
    __swig_getmethods__["inputDimWidth"] = _vcam.Network1Par_inputDimWidth_get
    if _newclass:
        inputDimWidth = _swig_property(_vcam.Network1Par_inputDimWidth_get, _vcam.Network1Par_inputDimWidth_set)
    __swig_setmethods__["inputDimHeight"] = _vcam.Network1Par_inputDimHeight_set
    __swig_getmethods__["inputDimHeight"] = _vcam.Network1Par_inputDimHeight_get
    if _newclass:
        inputDimHeight = _swig_property(_vcam.Network1Par_inputDimHeight_get, _vcam.Network1Par_inputDimHeight_set)
    __swig_setmethods__["inputFormat"] = _vcam.Network1Par_inputFormat_set
    __swig_getmethods__["inputFormat"] = _vcam.Network1Par_inputFormat_get
    if _newclass:
        inputFormat = _swig_property(_vcam.Network1Par_inputFormat_get, _vcam.Network1Par_inputFormat_set)
    __swig_setmethods__["meanValue"] = _vcam.Network1Par_meanValue_set
    __swig_getmethods__["meanValue"] = _vcam.Network1Par_meanValue_get
    if _newclass:
        meanValue = _swig_property(_vcam.Network1Par_meanValue_get, _vcam.Network1Par_meanValue_set)
    __swig_setmethods__["stdValue"] = _vcam.Network1Par_stdValue_set
    __swig_getmethods__["stdValue"] = _vcam.Network1Par_stdValue_get
    if _newclass:
        stdValue = _swig_property(_vcam.Network1Par_stdValue_get, _vcam.Network1Par_stdValue_set)
    __swig_setmethods__["isOutputYUV"] = _vcam.Network1Par_isOutputYUV_set
    __swig_getmethods__["isOutputYUV"] = _vcam.Network1Par_isOutputYUV_get
    if _newclass:
        isOutputYUV = _swig_property(_vcam.Network1Par_isOutputYUV_get, _vcam.Network1Par_isOutputYUV_set)
    __swig_setmethods__["isOutputH26X"] = _vcam.Network1Par_isOutputH26X_set
    __swig_getmethods__["isOutputH26X"] = _vcam.Network1Par_isOutputH26X_get
    if _newclass:
        isOutputH26X = _swig_property(_vcam.Network1Par_isOutputH26X_get, _vcam.Network1Par_isOutputH26X_set)
    __swig_setmethods__["isOutputJPEG"] = _vcam.Network1Par_isOutputJPEG_set
    __swig_getmethods__["isOutputJPEG"] = _vcam.Network1Par_isOutputJPEG_get
    if _newclass:
        isOutputJPEG = _swig_property(_vcam.Network1Par_isOutputJPEG_get, _vcam.Network1Par_isOutputJPEG_set)
    __swig_setmethods__["mode"] = _vcam.Network1Par_mode_set
    __swig_getmethods__["mode"] = _vcam.Network1Par_mode_get
    if _newclass:
        mode = _swig_property(_vcam.Network1Par_mode_get, _vcam.Network1Par_mode_set)
    __swig_setmethods__["extInputs"] = _vcam.Network1Par_extInputs_set
    __swig_getmethods__["extInputs"] = _vcam.Network1Par_extInputs_get
    if _newclass:
        extInputs = _swig_property(_vcam.Network1Par_extInputs_get, _vcam.Network1Par_extInputs_set)
    __swig_setmethods__["modelCascade"] = _vcam.Network1Par_modelCascade_set
    __swig_getmethods__["modelCascade"] = _vcam.Network1Par_modelCascade_get
    if _newclass:
        modelCascade = _swig_property(_vcam.Network1Par_modelCascade_get, _vcam.Network1Par_modelCascade_set)
    __swig_setmethods__["inferenceACC"] = _vcam.Network1Par_inferenceACC_set
    __swig_getmethods__["inferenceACC"] = _vcam.Network1Par_inferenceACC_get
    if _newclass:
        inferenceACC = _swig_property(_vcam.Network1Par_inferenceACC_get, _vcam.Network1Par_inferenceACC_set)

    def __init__(self):
        this = _vcam.new_Network1Par()
        try:
            self.this.append(this)
        except __builtin__.Exception:
            self.this = this
    __swig_destroy__ = _vcam.delete_Network1Par
    __del__ = lambda self: None
Network1Par_swigregister = _vcam.Network1Par_swigregister
Network1Par_swigregister(Network1Par)

class Network2Par(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, Network2Par, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, Network2Par, name)
    __repr__ = _swig_repr
    __swig_setmethods__["startXAdj"] = _vcam.Network2Par_startXAdj_set
    __swig_getmethods__["startXAdj"] = _vcam.Network2Par_startXAdj_get
    if _newclass:
        startXAdj = _swig_property(_vcam.Network2Par_startXAdj_get, _vcam.Network2Par_startXAdj_set)
    __swig_setmethods__["startYAdj"] = _vcam.Network2Par_startYAdj_set
    __swig_getmethods__["startYAdj"] = _vcam.Network2Par_startYAdj_get
    if _newclass:
        startYAdj = _swig_property(_vcam.Network2Par_startYAdj_get, _vcam.Network2Par_startYAdj_set)
    __swig_setmethods__["endXAdj"] = _vcam.Network2Par_endXAdj_set
    __swig_getmethods__["endXAdj"] = _vcam.Network2Par_endXAdj_get
    if _newclass:
        endXAdj = _swig_property(_vcam.Network2Par_endXAdj_get, _vcam.Network2Par_endXAdj_set)
    __swig_setmethods__["endYAdj"] = _vcam.Network2Par_endYAdj_set
    __swig_getmethods__["endYAdj"] = _vcam.Network2Par_endYAdj_get
    if _newclass:
        endYAdj = _swig_property(_vcam.Network2Par_endYAdj_get, _vcam.Network2Par_endYAdj_set)
    __swig_setmethods__["labelMask"] = _vcam.Network2Par_labelMask_set
    __swig_getmethods__["labelMask"] = _vcam.Network2Par_labelMask_get
    if _newclass:
        labelMask = _swig_property(_vcam.Network2Par_labelMask_get, _vcam.Network2Par_labelMask_set)
    __swig_setmethods__["minConf"] = _vcam.Network2Par_minConf_set
    __swig_getmethods__["minConf"] = _vcam.Network2Par_minConf_get
    if _newclass:
        minConf = _swig_property(_vcam.Network2Par_minConf_get, _vcam.Network2Par_minConf_set)
    __swig_setmethods__["inputDimWidth"] = _vcam.Network2Par_inputDimWidth_set
    __swig_getmethods__["inputDimWidth"] = _vcam.Network2Par_inputDimWidth_get
    if _newclass:
        inputDimWidth = _swig_property(_vcam.Network2Par_inputDimWidth_get, _vcam.Network2Par_inputDimWidth_set)
    __swig_setmethods__["inputDimHeight"] = _vcam.Network2Par_inputDimHeight_set
    __swig_getmethods__["inputDimHeight"] = _vcam.Network2Par_inputDimHeight_get
    if _newclass:
        inputDimHeight = _swig_property(_vcam.Network2Par_inputDimHeight_get, _vcam.Network2Par_inputDimHeight_set)
    __swig_setmethods__["inputFormat"] = _vcam.Network2Par_inputFormat_set
    __swig_getmethods__["inputFormat"] = _vcam.Network2Par_inputFormat_get
    if _newclass:
        inputFormat = _swig_property(_vcam.Network2Par_inputFormat_get, _vcam.Network2Par_inputFormat_set)
    __swig_setmethods__["meanValue"] = _vcam.Network2Par_meanValue_set
    __swig_getmethods__["meanValue"] = _vcam.Network2Par_meanValue_get
    if _newclass:
        meanValue = _swig_property(_vcam.Network2Par_meanValue_get, _vcam.Network2Par_meanValue_set)
    __swig_setmethods__["stdValue"] = _vcam.Network2Par_stdValue_set
    __swig_getmethods__["stdValue"] = _vcam.Network2Par_stdValue_get
    if _newclass:
        stdValue = _swig_property(_vcam.Network2Par_stdValue_get, _vcam.Network2Par_stdValue_set)
    __swig_setmethods__["extInputs"] = _vcam.Network2Par_extInputs_set
    __swig_getmethods__["extInputs"] = _vcam.Network2Par_extInputs_get
    if _newclass:
        extInputs = _swig_property(_vcam.Network2Par_extInputs_get, _vcam.Network2Par_extInputs_set)
    __swig_setmethods__["modelCascade"] = _vcam.Network2Par_modelCascade_set
    __swig_getmethods__["modelCascade"] = _vcam.Network2Par_modelCascade_get
    if _newclass:
        modelCascade = _swig_property(_vcam.Network2Par_modelCascade_get, _vcam.Network2Par_modelCascade_set)

    def __init__(self):
        this = _vcam.new_Network2Par()
        try:
            self.this.append(this)
        except __builtin__.Exception:
            self.this = this
    __swig_destroy__ = _vcam.delete_Network2Par
    __del__ = lambda self: None
Network2Par_swigregister = _vcam.Network2Par_swigregister
Network2Par_swigregister(Network2Par)

class frameSpecOut(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, frameSpecOut, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, frameSpecOut, name)
    __repr__ = _swig_repr
    __swig_setmethods__["type"] = _vcam.frameSpecOut_type_set
    __swig_getmethods__["type"] = _vcam.frameSpecOut_type_get
    if _newclass:
        type = _swig_property(_vcam.frameSpecOut_type_get, _vcam.frameSpecOut_type_set)
    __swig_setmethods__["seqNo"] = _vcam.frameSpecOut_seqNo_set
    __swig_getmethods__["seqNo"] = _vcam.frameSpecOut_seqNo_get
    if _newclass:
        seqNo = _swig_property(_vcam.frameSpecOut_seqNo_get, _vcam.frameSpecOut_seqNo_set)
    __swig_setmethods__["size"] = _vcam.frameSpecOut_size_set
    __swig_getmethods__["size"] = _vcam.frameSpecOut_size_get
    if _newclass:
        size = _swig_property(_vcam.frameSpecOut_size_get, _vcam.frameSpecOut_size_set)
    __swig_setmethods__["res"] = _vcam.frameSpecOut_res_set
    __swig_getmethods__["res"] = _vcam.frameSpecOut_res_get
    if _newclass:
        res = _swig_property(_vcam.frameSpecOut_res_get, _vcam.frameSpecOut_res_set)

    def __init__(self):
        this = _vcam.new_frameSpecOut()
        try:
            self.this.append(this)
        except __builtin__.Exception:
            self.this = this
    __swig_destroy__ = _vcam.delete_frameSpecOut
    __del__ = lambda self: None
frameSpecOut_swigregister = _vcam.frameSpecOut_swigregister
frameSpecOut_swigregister(frameSpecOut)


def GetYuvData(pbuf: 'char *') -> "int":
    return _vcam.GetYuvData(pbuf)
GetYuvData = _vcam.GetYuvData

def GetMetaData(pbuf: 'char *') -> "int":
    return _vcam.GetMetaData(pbuf)
GetMetaData = _vcam.GetMetaData

def GetH26xData(pbuf: 'char *') -> "int":
    return _vcam.GetH26xData(pbuf)
GetH26xData = _vcam.GetH26xData

def GetJpegData(buf: 'char *', slen: 'int') -> "int":
    return _vcam.GetJpegData(buf, slen)
GetJpegData = _vcam.GetJpegData

def get_sdk_version() -> "char *":
    return _vcam.get_sdk_version()
get_sdk_version = _vcam.get_sdk_version

def load_fw(bootExe: 'char const *', firmware: 'char const *') -> "int":
    return _vcam.load_fw(bootExe, firmware)
load_fw = _vcam.load_fw

def load_fwExt(bootExe: 'char const *', firmware: 'char const *', pid: 'int') -> "int":
    return _vcam.load_fwExt(bootExe, firmware, pid)
load_fwExt = _vcam.load_fwExt

def sdk_init(cb: 'vscRecvCb', param: 'void *', blob_path: 'char const *', cam: 'CameraInfo', cam_Len: 'int') -> "int":
    return _vcam.sdk_init(cb, param, blob_path, cam, cam_Len)
sdk_init = _vcam.sdk_init

def sdk_init_ex(cb: 'vscRecvCb', param: 'void *', blob_path: 'char const *', cam: 'Network1Par', cam_Len: 'int') -> "int":
    return _vcam.sdk_init_ex(cb, param, blob_path, cam, cam_Len)
sdk_init_ex = _vcam.sdk_init_ex

def sdk_net2_init(cb: 'vscRecvCb', param: 'void *', blob_path: 'char const *', par: 'Network1Par', par_Len: 'int', blob2_path: 'char const *', par2: 'Network2Par', par2_Len: 'int') -> "int":
    return _vcam.sdk_net2_init(cb, param, blob_path, par, par_Len, blob2_path, par2, par2_Len)
sdk_net2_init = _vcam.sdk_net2_init

def sdk_uninit() -> "void":
    return _vcam.sdk_uninit()
sdk_uninit = _vcam.sdk_uninit

def get_usb_version() -> "int":
    return _vcam.get_usb_version()
get_usb_version = _vcam.get_usb_version

def get_err_no() -> "int":
    return _vcam.get_err_no()
get_err_no = _vcam.get_err_no

def get_init_error(size: 'int') -> "char *":
    return _vcam.get_init_error(size)
get_init_error = _vcam.get_init_error

def read_yuv_data(pbuf: 'char *', size: 'int *', blocked: 'int') -> "int":
    return _vcam.read_yuv_data(pbuf, size, blocked)
read_yuv_data = _vcam.read_yuv_data

def read_26x_data(pbuf: 'char *', size: 'int *', blocked: 'int') -> "int":
    return _vcam.read_26x_data(pbuf, size, blocked)
read_26x_data = _vcam.read_26x_data

def read_jpg_data(pbuf: 'char *', size: 'int *', blocked: 'int') -> "int":
    return _vcam.read_jpg_data(pbuf, size, blocked)
read_jpg_data = _vcam.read_jpg_data

def read_meta_data(pbuf: 'char *', size: 'int *', blocked: 'int') -> "int":
    return _vcam.read_meta_data(pbuf, size, blocked)
read_meta_data = _vcam.read_meta_data

def down_image_data(data: 'char const *', len: 'int') -> "int":
    return _vcam.down_image_data(data, len)
down_image_data = _vcam.down_image_data

def get_meta_size() -> "int":
    return _vcam.get_meta_size()
get_meta_size = _vcam.get_meta_size

def GetMetaDataExt(pbuf: 'char *') -> "int *, int *, int *":
    return _vcam.GetMetaDataExt(pbuf)
GetMetaDataExt = _vcam.GetMetaDataExt
MAX_MODE_SIZE = _vcam.MAX_MODE_SIZE
CAMERA_CONTROL__AE_AUTO__FLASH_MODE__OFF = _vcam.CAMERA_CONTROL__AE_AUTO__FLASH_MODE__OFF
CAMERA_CONTROL__AE_AUTO__FLASH_MODE__AUTO = _vcam.CAMERA_CONTROL__AE_AUTO__FLASH_MODE__AUTO
CAMERA_CONTROL__AWB_MODE__OFF = _vcam.CAMERA_CONTROL__AWB_MODE__OFF
CAMERA_CONTROL__AWB_MODE__AUTO = _vcam.CAMERA_CONTROL__AWB_MODE__AUTO
CAMERA_CONTROL__AF_MODE_OFF = _vcam.CAMERA_CONTROL__AF_MODE_OFF
CAMERA_CONTROL__AF_MODE_AUTO = _vcam.CAMERA_CONTROL__AF_MODE_AUTO
VIDEO_OUT_DISABLE = _vcam.VIDEO_OUT_DISABLE
VIDEO_OUT_SINGLE = _vcam.VIDEO_OUT_SINGLE
VIDEO_OUT_CONTINUOUS = _vcam.VIDEO_OUT_CONTINUOUS
PWM_OUT_DISABLE = _vcam.PWM_OUT_DISABLE
PWM_OUT_ENABLE = _vcam.PWM_OUT_ENABLE
class SensorModesConfig(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, SensorModesConfig, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, SensorModesConfig, name)
    __repr__ = _swig_repr
    __swig_setmethods__["moduleName"] = _vcam.SensorModesConfig_moduleName_set
    __swig_getmethods__["moduleName"] = _vcam.SensorModesConfig_moduleName_get
    if _newclass:
        moduleName = _swig_property(_vcam.SensorModesConfig_moduleName_get, _vcam.SensorModesConfig_moduleName_set)
    __swig_setmethods__["camWidth"] = _vcam.SensorModesConfig_camWidth_set
    __swig_getmethods__["camWidth"] = _vcam.SensorModesConfig_camWidth_get
    if _newclass:
        camWidth = _swig_property(_vcam.SensorModesConfig_camWidth_get, _vcam.SensorModesConfig_camWidth_set)
    __swig_setmethods__["camHeight"] = _vcam.SensorModesConfig_camHeight_set
    __swig_getmethods__["camHeight"] = _vcam.SensorModesConfig_camHeight_get
    if _newclass:
        camHeight = _swig_property(_vcam.SensorModesConfig_camHeight_get, _vcam.SensorModesConfig_camHeight_set)
    __swig_setmethods__["camFps"] = _vcam.SensorModesConfig_camFps_set
    __swig_getmethods__["camFps"] = _vcam.SensorModesConfig_camFps_get
    if _newclass:
        camFps = _swig_property(_vcam.SensorModesConfig_camFps_get, _vcam.SensorModesConfig_camFps_set)
    __swig_setmethods__["AFmode"] = _vcam.SensorModesConfig_AFmode_set
    __swig_getmethods__["AFmode"] = _vcam.SensorModesConfig_AFmode_get
    if _newclass:
        AFmode = _swig_property(_vcam.SensorModesConfig_AFmode_get, _vcam.SensorModesConfig_AFmode_set)
    __swig_setmethods__["maxEXP"] = _vcam.SensorModesConfig_maxEXP_set
    __swig_getmethods__["maxEXP"] = _vcam.SensorModesConfig_maxEXP_get
    if _newclass:
        maxEXP = _swig_property(_vcam.SensorModesConfig_maxEXP_get, _vcam.SensorModesConfig_maxEXP_set)
    __swig_setmethods__["minGain"] = _vcam.SensorModesConfig_minGain_set
    __swig_getmethods__["minGain"] = _vcam.SensorModesConfig_minGain_get
    if _newclass:
        minGain = _swig_property(_vcam.SensorModesConfig_minGain_get, _vcam.SensorModesConfig_minGain_set)
    __swig_setmethods__["maxGain"] = _vcam.SensorModesConfig_maxGain_set
    __swig_getmethods__["maxGain"] = _vcam.SensorModesConfig_maxGain_get
    if _newclass:
        maxGain = _swig_property(_vcam.SensorModesConfig_maxGain_get, _vcam.SensorModesConfig_maxGain_set)

    def __init__(self):
        this = _vcam.new_SensorModesConfig()
        try:
            self.this.append(this)
        except __builtin__.Exception:
            self.this = this
    __swig_destroy__ = _vcam.delete_SensorModesConfig
    __del__ = lambda self: None
SensorModesConfig_swigregister = _vcam.SensorModesConfig_swigregister
SensorModesConfig_swigregister(SensorModesConfig)

class Encrypt_t(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, Encrypt_t, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, Encrypt_t, name)
    __repr__ = _swig_repr
    __swig_setmethods__["key_version"] = _vcam.Encrypt_t_key_version_set
    __swig_getmethods__["key_version"] = _vcam.Encrypt_t_key_version_get
    if _newclass:
        key_version = _swig_property(_vcam.Encrypt_t_key_version_get, _vcam.Encrypt_t_key_version_set)
    __swig_setmethods__["lock"] = _vcam.Encrypt_t_lock_set
    __swig_getmethods__["lock"] = _vcam.Encrypt_t_lock_get
    if _newclass:
        lock = _swig_property(_vcam.Encrypt_t_lock_get, _vcam.Encrypt_t_lock_set)
    __swig_setmethods__["hw_config"] = _vcam.Encrypt_t_hw_config_set
    __swig_getmethods__["hw_config"] = _vcam.Encrypt_t_hw_config_get
    if _newclass:
        hw_config = _swig_property(_vcam.Encrypt_t_hw_config_get, _vcam.Encrypt_t_hw_config_set)
    __swig_setmethods__["accelerate_num"] = _vcam.Encrypt_t_accelerate_num_set
    __swig_getmethods__["accelerate_num"] = _vcam.Encrypt_t_accelerate_num_get
    if _newclass:
        accelerate_num = _swig_property(_vcam.Encrypt_t_accelerate_num_get, _vcam.Encrypt_t_accelerate_num_set)
    __swig_setmethods__["hw_version"] = _vcam.Encrypt_t_hw_version_set
    __swig_getmethods__["hw_version"] = _vcam.Encrypt_t_hw_version_get
    if _newclass:
        hw_version = _swig_property(_vcam.Encrypt_t_hw_version_get, _vcam.Encrypt_t_hw_version_set)
    __swig_setmethods__["hw_version_reserve"] = _vcam.Encrypt_t_hw_version_reserve_set
    __swig_getmethods__["hw_version_reserve"] = _vcam.Encrypt_t_hw_version_reserve_get
    if _newclass:
        hw_version_reserve = _swig_property(_vcam.Encrypt_t_hw_version_reserve_get, _vcam.Encrypt_t_hw_version_reserve_set)
    __swig_setmethods__["batch_num"] = _vcam.Encrypt_t_batch_num_set
    __swig_getmethods__["batch_num"] = _vcam.Encrypt_t_batch_num_get
    if _newclass:
        batch_num = _swig_property(_vcam.Encrypt_t_batch_num_get, _vcam.Encrypt_t_batch_num_set)
    __swig_setmethods__["reserve"] = _vcam.Encrypt_t_reserve_set
    __swig_getmethods__["reserve"] = _vcam.Encrypt_t_reserve_get
    if _newclass:
        reserve = _swig_property(_vcam.Encrypt_t_reserve_get, _vcam.Encrypt_t_reserve_set)

    def __init__(self):
        this = _vcam.new_Encrypt_t()
        try:
            self.this.append(this)
        except __builtin__.Exception:
            self.this = this
    __swig_destroy__ = _vcam.delete_Encrypt_t
    __del__ = lambda self: None
Encrypt_t_swigregister = _vcam.Encrypt_t_swigregister
Encrypt_t_swigregister(Encrypt_t)

class SensorModesList(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, SensorModesList, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, SensorModesList, name)
    __repr__ = _swig_repr
    __swig_setmethods__["num"] = _vcam.SensorModesList_num_set
    __swig_getmethods__["num"] = _vcam.SensorModesList_num_get
    if _newclass:
        num = _swig_property(_vcam.SensorModesList_num_get, _vcam.SensorModesList_num_set)
    __swig_setmethods__["mode"] = _vcam.SensorModesList_mode_set
    __swig_getmethods__["mode"] = _vcam.SensorModesList_mode_get
    if _newclass:
        mode = _swig_property(_vcam.SensorModesList_mode_get, _vcam.SensorModesList_mode_set)

    def __init__(self):
        this = _vcam.new_SensorModesList()
        try:
            self.this.append(this)
        except __builtin__.Exception:
            self.this = this
    __swig_destroy__ = _vcam.delete_SensorModesList
    __del__ = lambda self: None
SensorModesList_swigregister = _vcam.SensorModesList_swigregister
SensorModesList_swigregister(SensorModesList)

class CameraSensor(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, CameraSensor, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, CameraSensor, name)
    __repr__ = _swig_repr

    def __init__(self):
        this = _vcam.new_CameraSensor()
        try:
            self.this.append(this)
        except __builtin__.Exception:
            self.this = this
    __swig_destroy__ = _vcam.delete_CameraSensor
    __del__ = lambda self: None

    def GetFirstSensor(self, sensor: 'SensorModesConfig') -> "int":
        return _vcam.CameraSensor_GetFirstSensor(self, sensor)

    def GetNextSensor(self, sensor: 'SensorModesConfig') -> "int":
        return _vcam.CameraSensor_GetNextSensor(self, sensor)
CameraSensor_swigregister = _vcam.CameraSensor_swigregister
CameraSensor_swigregister(CameraSensor)


def camera_control_get_features(list: 'SensorModesList') -> "int":
    return _vcam.camera_control_get_features(list)
camera_control_get_features = _vcam.camera_control_get_features

def camera_control_get_sensorinfo(info: 'SensorModesConfig', num: 'int') -> "int":
    return _vcam.camera_control_get_sensorinfo(info, num)
camera_control_get_sensorinfo = _vcam.camera_control_get_sensorinfo

def camera_control_af_mode(af_mode: 'camera_ctrl_af_mode') -> "int":
    return _vcam.camera_control_af_mode(af_mode)
camera_control_af_mode = _vcam.camera_control_af_mode

def camera_control_lens_move(lens_position: 'uint32_t') -> "int":
    return _vcam.camera_control_lens_move(lens_position)
camera_control_lens_move = _vcam.camera_control_lens_move

def camera_control_focus_trigger() -> "int":
    return _vcam.camera_control_focus_trigger()
camera_control_focus_trigger = _vcam.camera_control_focus_trigger

def camera_control_ae_mode(flash_mode: 'camera_ctrl_ae_mode') -> "int":
    return _vcam.camera_control_ae_mode(flash_mode)
camera_control_ae_mode = _vcam.camera_control_ae_mode

def camera_control_ae_set_exp(exp_compensation: 'uint32_t') -> "int":
    return _vcam.camera_control_ae_set_exp(exp_compensation)
camera_control_ae_set_exp = _vcam.camera_control_ae_set_exp

def camera_control_ae_set_gain(iso_val: 'uint32_t') -> "int":
    return _vcam.camera_control_ae_set_gain(iso_val)
camera_control_ae_set_gain = _vcam.camera_control_ae_set_gain

def camera_control_awb_mode(awb_mode: 'camera_ctrl_awb_mode') -> "int":
    return _vcam.camera_control_awb_mode(awb_mode)
camera_control_awb_mode = _vcam.camera_control_awb_mode

def camera_video_out(video_type: 'int', mode: 'camera_ctrl_video_out') -> "int":
    return _vcam.camera_video_out(video_type, mode)
camera_video_out = _vcam.camera_video_out

def camera_select_sensor(sensorid: 'int') -> "int":
    return _vcam.camera_select_sensor(sensorid)
camera_select_sensor = _vcam.camera_select_sensor

def device_control_get_fw_version(fw: 'char *', len: 'int') -> "int":
    return _vcam.device_control_get_fw_version(fw, len)
device_control_get_fw_version = _vcam.device_control_get_fw_version

def device_control_get_device_id(id: 'uint8_t *', size: 'int') -> "int":
    return _vcam.device_control_get_device_id(id, size)
device_control_get_device_id = _vcam.device_control_get_device_id

def camera_get_ncc_id() -> "char *":
    return _vcam.camera_get_ncc_id()
camera_get_ncc_id = _vcam.camera_get_ncc_id

def camera_get_fw_version() -> "char *":
    return _vcam.camera_get_fw_version()
camera_get_fw_version = _vcam.camera_get_fw_version

def device_control_get_device_info(info: 'Encrypt_t') -> "int":
    return _vcam.device_control_get_device_info(info)
device_control_get_device_info = _vcam.device_control_get_device_info

def device_control_set_device_info(info: 'Encrypt_t') -> "int":
    return _vcam.device_control_set_device_info(info)
device_control_set_device_info = _vcam.device_control_set_device_info

def camera_control_set_bps(value: 'int') -> "int":
    return _vcam.camera_control_set_bps(value)
camera_control_set_bps = _vcam.camera_control_set_bps
F32_RND_NEAREST_EVEN = _vcam.F32_RND_NEAREST_EVEN
F32_RND_MINUS_INF = _vcam.F32_RND_MINUS_INF
F32_RND_PLUS_INF = _vcam.F32_RND_PLUS_INF
F32_RND_TO_ZERO = _vcam.F32_RND_TO_ZERO
F32_DETECT_TINY_AFTER_RND = _vcam.F32_DETECT_TINY_AFTER_RND
F32_DETECT_TINY_BEFORE_RND = _vcam.F32_DETECT_TINY_BEFORE_RND
F32_EX_INEXACT = _vcam.F32_EX_INEXACT
F32_EX_DIV_BY_ZERO = _vcam.F32_EX_DIV_BY_ZERO
F32_EX_INVALID = _vcam.F32_EX_INVALID
F32_EX_UNDERFLOW = _vcam.F32_EX_UNDERFLOW
F32_EX_OVERFLOW = _vcam.F32_EX_OVERFLOW
F32_NAN_DEFAULT = _vcam.F32_NAN_DEFAULT

def f32Tof16(x: 'float') -> "unsigned int":
    return _vcam.f32Tof16(x)
f32Tof16 = _vcam.f32Tof16

def f16Tof32(x: 'unsigned int') -> "float":
    return _vcam.f16Tof32(x)
f16Tof32 = _vcam.f16Tof32
# This file is compatible with both classic and new-style classes.


