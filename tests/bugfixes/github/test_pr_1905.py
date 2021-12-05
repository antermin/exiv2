# -*- coding: utf-8 -*-

from system_tests import CaseMeta, path

class TestExifTagsInTaglist(metaclass=CaseMeta):

# The taglist program outputs lots of data on all Exif tags.
# Extract only the keys and compare
    filename = "$tmp_path/TestExifTagsInTaglist.txt"
    commands = ["$taglist Exif > $filename",
                "cut -d, -f5 $filename"]

    stdout = ["""""",
"""Exif.Image.ProcessingSoftware
Exif.Image.NewSubfileType
Exif.Image.SubfileType
Exif.Image.ImageWidth
Exif.Image.ImageLength
Exif.Image.BitsPerSample
Exif.Image.Compression
Exif.Image.PhotometricInterpretation
Exif.Image.Thresholding
Exif.Image.CellWidth
Exif.Image.CellLength
Exif.Image.FillOrder
Exif.Image.DocumentName
Exif.Image.ImageDescription
Exif.Image.Make
Exif.Image.Model
Exif.Image.StripOffsets
Exif.Image.Orientation
Exif.Image.SamplesPerPixel
Exif.Image.RowsPerStrip
Exif.Image.StripByteCounts
Exif.Image.XResolution
Exif.Image.YResolution
Exif.Image.PlanarConfiguration
Exif.Image.PageName
Exif.Image.XPosition
Exif.Image.YPosition
Exif.Image.GrayResponseUnit
Exif.Image.GrayResponseCurve
Exif.Image.T4Options
Exif.Image.T6Options
Exif.Image.ResolutionUnit
Exif.Image.PageNumber
Exif.Image.TransferFunction
Exif.Image.Software
Exif.Image.DateTime
Exif.Image.Artist
Exif.Image.HostComputer
Exif.Image.Predictor
Exif.Image.WhitePoint
Exif.Image.PrimaryChromaticities
Exif.Image.ColorMap
Exif.Image.HalftoneHints
Exif.Image.TileWidth
Exif.Image.TileLength
Exif.Image.TileOffsets
Exif.Image.TileByteCounts
Exif.Image.SubIFDs
Exif.Image.InkSet
Exif.Image.InkNames
Exif.Image.NumberOfInks
Exif.Image.DotRange
Exif.Image.TargetPrinter
Exif.Image.ExtraSamples
Exif.Image.SampleFormat
Exif.Image.SMinSampleValue
Exif.Image.SMaxSampleValue
Exif.Image.TransferRange
Exif.Image.ClipPath
Exif.Image.XClipPathUnits
Exif.Image.YClipPathUnits
Exif.Image.Indexed
Exif.Image.JPEGTables
Exif.Image.OPIProxy
Exif.Image.JPEGProc
Exif.Image.JPEGInterchangeFormat
Exif.Image.JPEGInterchangeFormatLength
Exif.Image.JPEGRestartInterval
Exif.Image.JPEGLosslessPredictors
Exif.Image.JPEGPointTransforms
Exif.Image.JPEGQTables
Exif.Image.JPEGDCTables
Exif.Image.JPEGACTables
Exif.Image.YCbCrCoefficients
Exif.Image.YCbCrSubSampling
Exif.Image.YCbCrPositioning
Exif.Image.ReferenceBlackWhite
Exif.Image.XMLPacket
Exif.Image.Rating
Exif.Image.RatingPercent
Exif.Image.VignettingCorrParams
Exif.Image.ChromaticAberrationCorrParams
Exif.Image.DistortionCorrParams
Exif.Image.ImageID
Exif.Image.CFARepeatPatternDim
Exif.Image.CFAPattern
Exif.Image.BatteryLevel
Exif.Image.Copyright
Exif.Image.ExposureTime
Exif.Image.FNumber
Exif.Image.IPTCNAA
Exif.Image.ImageResources
Exif.Image.ExifTag
Exif.Image.InterColorProfile
Exif.Image.ExposureProgram
Exif.Image.SpectralSensitivity
Exif.Image.GPSTag
Exif.Image.ISOSpeedRatings
Exif.Image.OECF
Exif.Image.Interlace
Exif.Image.TimeZoneOffset
Exif.Image.SelfTimerMode
Exif.Image.DateTimeOriginal
Exif.Image.CompressedBitsPerPixel
Exif.Image.ShutterSpeedValue
Exif.Image.ApertureValue
Exif.Image.BrightnessValue
Exif.Image.ExposureBiasValue
Exif.Image.MaxApertureValue
Exif.Image.SubjectDistance
Exif.Image.MeteringMode
Exif.Image.LightSource
Exif.Image.Flash
Exif.Image.FocalLength
Exif.Image.FlashEnergy
Exif.Image.SpatialFrequencyResponse
Exif.Image.Noise
Exif.Image.FocalPlaneXResolution
Exif.Image.FocalPlaneYResolution
Exif.Image.FocalPlaneResolutionUnit
Exif.Image.ImageNumber
Exif.Image.SecurityClassification
Exif.Image.ImageHistory
Exif.Image.SubjectLocation
Exif.Image.ExposureIndex
Exif.Image.TIFFEPStandardID
Exif.Image.SensingMethod
Exif.Image.XPTitle
Exif.Image.XPComment
Exif.Image.XPAuthor
Exif.Image.XPKeywords
Exif.Image.XPSubject
Exif.Image.PrintImageMatching
Exif.Image.DNGVersion
Exif.Image.DNGBackwardVersion
Exif.Image.UniqueCameraModel
Exif.Image.LocalizedCameraModel
Exif.Image.CFAPlaneColor
Exif.Image.CFALayout
Exif.Image.LinearizationTable
Exif.Image.BlackLevelRepeatDim
Exif.Image.BlackLevel
Exif.Image.BlackLevelDeltaH
Exif.Image.BlackLevelDeltaV
Exif.Image.WhiteLevel
Exif.Image.DefaultScale
Exif.Image.DefaultCropOrigin
Exif.Image.DefaultCropSize
Exif.Image.ColorMatrix1
Exif.Image.ColorMatrix2
Exif.Image.CameraCalibration1
Exif.Image.CameraCalibration2
Exif.Image.ReductionMatrix1
Exif.Image.ReductionMatrix2
Exif.Image.AnalogBalance
Exif.Image.AsShotNeutral
Exif.Image.AsShotWhiteXY
Exif.Image.BaselineExposure
Exif.Image.BaselineNoise
Exif.Image.BaselineSharpness
Exif.Image.BayerGreenSplit
Exif.Image.LinearResponseLimit
Exif.Image.CameraSerialNumber
Exif.Image.LensInfo
Exif.Image.ChromaBlurRadius
Exif.Image.AntiAliasStrength
Exif.Image.ShadowScale
Exif.Image.DNGPrivateData
Exif.Image.MakerNoteSafety
Exif.Image.CalibrationIlluminant1
Exif.Image.CalibrationIlluminant2
Exif.Image.BestQualityScale
Exif.Image.RawDataUniqueID
Exif.Image.OriginalRawFileName
Exif.Image.OriginalRawFileData
Exif.Image.ActiveArea
Exif.Image.MaskedAreas
Exif.Image.AsShotICCProfile
Exif.Image.AsShotPreProfileMatrix
Exif.Image.CurrentICCProfile
Exif.Image.CurrentPreProfileMatrix
Exif.Image.ColorimetricReference
Exif.Image.CameraCalibrationSignature
Exif.Image.ProfileCalibrationSignature
Exif.Image.ExtraCameraProfiles
Exif.Image.AsShotProfileName
Exif.Image.NoiseReductionApplied
Exif.Image.ProfileName
Exif.Image.ProfileHueSatMapDims
Exif.Image.ProfileHueSatMapData1
Exif.Image.ProfileHueSatMapData2
Exif.Image.ProfileToneCurve
Exif.Image.ProfileEmbedPolicy
Exif.Image.ProfileCopyright
Exif.Image.ForwardMatrix1
Exif.Image.ForwardMatrix2
Exif.Image.PreviewApplicationName
Exif.Image.PreviewApplicationVersion
Exif.Image.PreviewSettingsName
Exif.Image.PreviewSettingsDigest
Exif.Image.PreviewColorSpace
Exif.Image.PreviewDateTime
Exif.Image.RawImageDigest
Exif.Image.OriginalRawFileDigest
Exif.Image.SubTileBlockSize
Exif.Image.RowInterleaveFactor
Exif.Image.ProfileLookTableDims
Exif.Image.ProfileLookTableData
Exif.Image.OpcodeList1
Exif.Image.OpcodeList2
Exif.Image.OpcodeList3
Exif.Image.NoiseProfile
Exif.Image.TimeCodes
Exif.Image.FrameRate
Exif.Image.TStop
Exif.Image.ReelName
Exif.Image.CameraLabel
Exif.Image.OriginalDefaultFinalSize
Exif.Image.OriginalBestQualityFinalSize
Exif.Image.OriginalDefaultCropSize
Exif.Image.ProfileHueSatMapEncoding
Exif.Image.ProfileLookTableEncoding
Exif.Image.BaselineExposureOffset
Exif.Image.DefaultBlackRender
Exif.Image.NewRawImageDigest
Exif.Image.RawToPreviewGain
Exif.Image.DefaultUserCrop
Exif.Image.DepthFormat
Exif.Image.DepthNear
Exif.Image.DepthFar
Exif.Image.DepthUnits
Exif.Image.DepthMeasureType
Exif.Image.EnhanceParams
Exif.Image.ProfileGainTableMap
Exif.Image.SemanticName
Exif.Image.SemanticInstanceID
Exif.Image.CalibrationIlluminant3
Exif.Image.CameraCalibration3
Exif.Image.ColorMatrix3
Exif.Image.ForwardMatrix3
Exif.Image.IlluminantData1
Exif.Image.IlluminantData2
Exif.Image.IlluminantData3
Exif.Image.ProfileHueSatMapData3
Exif.Image.ReductionMatrix3
Exif.Photo.ExposureTime
Exif.Photo.FNumber
Exif.Photo.ExposureProgram
Exif.Photo.SpectralSensitivity
Exif.Photo.ISOSpeedRatings
Exif.Photo.OECF
Exif.Photo.SensitivityType
Exif.Photo.StandardOutputSensitivity
Exif.Photo.RecommendedExposureIndex
Exif.Photo.ISOSpeed
Exif.Photo.ISOSpeedLatitudeyyy
Exif.Photo.ISOSpeedLatitudezzz
Exif.Photo.ExifVersion
Exif.Photo.DateTimeOriginal
Exif.Photo.DateTimeDigitized
Exif.Photo.OffsetTime
Exif.Photo.OffsetTimeOriginal
Exif.Photo.OffsetTimeDigitized
Exif.Photo.ComponentsConfiguration
Exif.Photo.CompressedBitsPerPixel
Exif.Photo.ShutterSpeedValue
Exif.Photo.ApertureValue
Exif.Photo.BrightnessValue
Exif.Photo.ExposureBiasValue
Exif.Photo.MaxApertureValue
Exif.Photo.SubjectDistance
Exif.Photo.MeteringMode
Exif.Photo.LightSource
Exif.Photo.Flash
Exif.Photo.FocalLength
Exif.Photo.SubjectArea
Exif.Photo.MakerNote
Exif.Photo.UserComment
Exif.Photo.SubSecTime
Exif.Photo.SubSecTimeOriginal
Exif.Photo.SubSecTimeDigitized
Exif.Photo.Temperature
Exif.Photo.Humidity
Exif.Photo.Pressure
Exif.Photo.WaterDepth
Exif.Photo.Acceleration
Exif.Photo.CameraElevationAngle
Exif.Photo.FlashpixVersion
Exif.Photo.ColorSpace
Exif.Photo.PixelXDimension
Exif.Photo.PixelYDimension
Exif.Photo.RelatedSoundFile
Exif.Photo.InteroperabilityTag
Exif.Photo.FlashEnergy
Exif.Photo.SpatialFrequencyResponse
Exif.Photo.FocalPlaneXResolution
Exif.Photo.FocalPlaneYResolution
Exif.Photo.FocalPlaneResolutionUnit
Exif.Photo.SubjectLocation
Exif.Photo.ExposureIndex
Exif.Photo.SensingMethod
Exif.Photo.FileSource
Exif.Photo.SceneType
Exif.Photo.CFAPattern
Exif.Photo.CustomRendered
Exif.Photo.ExposureMode
Exif.Photo.WhiteBalance
Exif.Photo.DigitalZoomRatio
Exif.Photo.FocalLengthIn35mmFilm
Exif.Photo.SceneCaptureType
Exif.Photo.GainControl
Exif.Photo.Contrast
Exif.Photo.Saturation
Exif.Photo.Sharpness
Exif.Photo.DeviceSettingDescription
Exif.Photo.SubjectDistanceRange
Exif.Photo.ImageUniqueID
Exif.Photo.CameraOwnerName
Exif.Photo.BodySerialNumber
Exif.Photo.LensSpecification
Exif.Photo.LensMake
Exif.Photo.LensModel
Exif.Photo.LensSerialNumber
Exif.Photo.CompositeImage
Exif.Photo.SourceImageNumberOfCompositeImage
Exif.Photo.SourceExposureTimesOfCompositeImage
Exif.Photo.Gamma
Exif.Iop.InteroperabilityIndex
Exif.Iop.InteroperabilityVersion
Exif.Iop.RelatedImageFileFormat
Exif.Iop.RelatedImageWidth
Exif.Iop.RelatedImageLength
Exif.GPSInfo.GPSVersionID
Exif.GPSInfo.GPSLatitudeRef
Exif.GPSInfo.GPSLatitude
Exif.GPSInfo.GPSLongitudeRef
Exif.GPSInfo.GPSLongitude
Exif.GPSInfo.GPSAltitudeRef
Exif.GPSInfo.GPSAltitude
Exif.GPSInfo.GPSTimeStamp
Exif.GPSInfo.GPSSatellites
Exif.GPSInfo.GPSStatus
Exif.GPSInfo.GPSMeasureMode
Exif.GPSInfo.GPSDOP
Exif.GPSInfo.GPSSpeedRef
Exif.GPSInfo.GPSSpeed
Exif.GPSInfo.GPSTrackRef
Exif.GPSInfo.GPSTrack
Exif.GPSInfo.GPSImgDirectionRef
Exif.GPSInfo.GPSImgDirection
Exif.GPSInfo.GPSMapDatum
Exif.GPSInfo.GPSDestLatitudeRef
Exif.GPSInfo.GPSDestLatitude
Exif.GPSInfo.GPSDestLongitudeRef
Exif.GPSInfo.GPSDestLongitude
Exif.GPSInfo.GPSDestBearingRef
Exif.GPSInfo.GPSDestBearing
Exif.GPSInfo.GPSDestDistanceRef
Exif.GPSInfo.GPSDestDistance
Exif.GPSInfo.GPSProcessingMethod
Exif.GPSInfo.GPSAreaInformation
Exif.GPSInfo.GPSDateStamp
Exif.GPSInfo.GPSDifferential
Exif.GPSInfo.GPSHPositioningError
Exif.MpfInfo.MPFVersion
Exif.MpfInfo.MPFNumberOfImages
Exif.MpfInfo.MPFImageList
Exif.MpfInfo.MPFImageUIDList
Exif.MpfInfo.MPFTotalFrames
Exif.MpfInfo.MPFIndividualNum
Exif.MpfInfo.MPFPanOrientation
Exif.MpfInfo.MPFPanOverlapH
Exif.MpfInfo.MPFPanOverlapV
Exif.MpfInfo.MPFBaseViewpointNum
Exif.MpfInfo.MPFConvergenceAngle
Exif.MpfInfo.MPFBaselineLength
Exif.MpfInfo.MPFVerticalDivergence
Exif.MpfInfo.MPFAxisDistanceX
Exif.MpfInfo.MPFAxisDistanceY
Exif.MpfInfo.MPFAxisDistanceZ
Exif.MpfInfo.MPFYawAngle
Exif.MpfInfo.MPFPitchAngle
Exif.MpfInfo.MPFRollAngle
"""
    ]
    stderr = ["",
              ""]
    retval = [0,
              0]