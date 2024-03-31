@Tags(["not-finished"])
import 'package:test/test.dart';

import 'package:opencv_dart/opencv_dart.dart' as cv;

const arucoImage6x6_250 = "test/images/aruco_6X6_250_6.png";
const arucoImage6x6_250_contour = "test/images/aruco_6X6_250_6_contour.png";
const arucoImage6x6_250_1 = "test/images/aruco_6X6_250_1.png";

void main() async {
  test('cv.ArucoDetector', () {
    final img = cv.imread(arucoImage6x6_250, flags: cv.IMREAD_COLOR);
    expect(img.isEmpty, false);

    final dict = cv.ArucoDictionary.predefined(cv.PredefinedDictionaryType.DICT_6X6_250);
    final params = cv.ArucoDetectorParameters.empty();
    final detector = cv.ArucoDetector.create(dict, params);

    final (_, ids, _) = detector.detectMarkers(img);
    expect(ids, [40, 98, 62, 23, 124, 203]);
  });

  test('cv.arucoDrawDetectedMarkers', () {
    final img = cv.imread(arucoImage6x6_250, flags: cv.IMREAD_COLOR);
    expect(img.isEmpty, false);
    final imgExpected = cv.imread(arucoImage6x6_250_contour, flags: cv.IMREAD_COLOR);
    expect(imgExpected.isEmpty, false);

    final dict = cv.ArucoDictionary.predefined(cv.PredefinedDictionaryType.DICT_6X6_250);
    final params = cv.ArucoDetectorParameters.empty();
    final detector = cv.ArucoDetector.create(dict, params);

    final (corners, ids, _) = detector.detectMarkers(img);
    expect(corners.length, greaterThan(0));
    cv.arucoDrawDetectedMarkers(img, corners, ids, cv.Scalar(200, 0, 0, 0));
    final diff = cv.Mat.empty();
    cv.absDiff(img, imgExpected, diff);
    cv.cvtColor(diff, diff, cv.COLOR_BGR2GRAY);
    expect(cv.countNonZero(diff), 0);
  });

  test('cv.arucoGenerateImageMarker', () {
    final imgExpected = cv.imread(arucoImage6x6_250_1, flags: cv.IMREAD_GRAYSCALE);
    expect(imgExpected.isEmpty, false);

    final img = cv.Mat.empty();
    cv.arucoGenerateImageMarker(cv.PredefinedDictionaryType.DICT_6X6_250, 1, 200, img, 1);

    final diff = cv.Mat.empty();
    cv.absDiff(img, imgExpected, diff);
    expect(cv.countNonZero(diff), 0);
  });

  test('cv.ArucoDetectorParameters', () {
    final int adaptiveThreshWinSizeMin = 4;
    final int adaptiveThreshWinSizeMax = 22;
    final int adaptiveThreshWinSizeStep = 1;
    final double adaptiveThreshConstant = 1.0;
    final double minMarkerPerimeterRate = 0.2;
    final double maxMarkerPerimeterRate = 0.5;
    final double polygonalApproxAccuracyRate = 1.0;
    final double minCornerDistanceRate = 0.1;
    final int minDistanceToBorder = 0;
    final double minMarkerDistanceRate = 1.0;
    final int cornerRefinementMethod = 1;
    final int cornerRefinementWinSize = 1;
    final int cornerRefinementMaxIterations = 1;
    final double cornerRefinementMinAccuracy = 0.5;
    final int markerBorderBits = 1;
    final int perspectiveRemovePixelPerCell = 1;
    final double perspectiveRemoveIgnoredMarginPerCell = 1.0;
    final double maxErroneousBitsInBorderRate = 0.5;
    final double minOtsuStdDev = .5;
    final double errorCorrectionRate = 0.2;
    final double aprilTagQuadDecimate = 0.5;
    final double aprilTagQuadSigma = 1;
    final int aprilTagMinClusterPixels = 1;
    final int aprilTagMaxNmaxima = 1;
    final double aprilTagCriticalRad = 0.2;
    final double aprilTagMaxLineFitMse = 0.2;
    final int aprilTagMinWhiteBlackDiff = 1;
    final int aprilTagDeglitch = 1;
    final bool detectInvertedMarker = false;
    final params = cv.ArucoDetectorParameters.empty()
      ..adaptiveThreshWinSizeMin = adaptiveThreshWinSizeMin
      ..adaptiveThreshWinSizeMax = adaptiveThreshWinSizeMax
      ..adaptiveThreshWinSizeStep = adaptiveThreshWinSizeStep
      ..adaptiveThreshConstant = adaptiveThreshConstant
      ..minMarkerPerimeterRate = minMarkerPerimeterRate
      ..maxMarkerPerimeterRate = maxMarkerPerimeterRate
      ..polygonalApproxAccuracyRate = polygonalApproxAccuracyRate
      ..minCornerDistanceRate = minCornerDistanceRate
      ..minDistanceToBorder = minDistanceToBorder
      ..minMarkerDistanceRate = minMarkerDistanceRate
      ..cornerRefinementMethod = cornerRefinementMethod
      ..cornerRefinementWinSize = cornerRefinementWinSize
      ..cornerRefinementMaxIterations = cornerRefinementMaxIterations
      ..cornerRefinementMinAccuracy = cornerRefinementMinAccuracy
      ..markerBorderBits = markerBorderBits
      ..perspectiveRemovePixelPerCell = perspectiveRemovePixelPerCell
      ..perspectiveRemoveIgnoredMarginPerCell = perspectiveRemoveIgnoredMarginPerCell
      ..maxErroneousBitsInBorderRate = maxErroneousBitsInBorderRate
      ..minOtsuStdDev = minOtsuStdDev
      ..errorCorrectionRate = errorCorrectionRate
      ..aprilTagQuadDecimate = aprilTagQuadDecimate
      ..aprilTagQuadSigma = aprilTagQuadSigma
      ..aprilTagMinClusterPixels = aprilTagMinClusterPixels
      ..aprilTagMaxNmaxima = aprilTagMaxNmaxima
      ..aprilTagCriticalRad = aprilTagCriticalRad
      ..aprilTagMaxLineFitMse = aprilTagMaxLineFitMse
      ..aprilTagMinWhiteBlackDiff = aprilTagMinWhiteBlackDiff
      ..aprilTagDeglitch = aprilTagDeglitch
      ..detectInvertedMarker = detectInvertedMarker;

    expect(params.adaptiveThreshWinSizeMin, adaptiveThreshWinSizeMin);
    expect(params.adaptiveThreshWinSizeMax, adaptiveThreshWinSizeMax);
    expect(params.adaptiveThreshWinSizeStep, adaptiveThreshWinSizeStep);
    expect(params.adaptiveThreshConstant, closeTo(adaptiveThreshConstant, 1e-4));
    expect(params.minMarkerPerimeterRate, closeTo(minMarkerPerimeterRate, 1e-4));
    expect(params.maxMarkerPerimeterRate, closeTo(maxMarkerPerimeterRate, 1e-4));
    expect(params.polygonalApproxAccuracyRate, closeTo(polygonalApproxAccuracyRate, 1e-4));
    expect(params.minCornerDistanceRate, closeTo(minCornerDistanceRate, 1e-4));
    expect(params.minDistanceToBorder, minDistanceToBorder);
    expect(params.minMarkerDistanceRate, closeTo(minMarkerDistanceRate, 1e-4));
    expect(params.cornerRefinementMethod, cornerRefinementMethod);
    expect(params.cornerRefinementWinSize, cornerRefinementWinSize);
    expect(params.cornerRefinementMaxIterations, cornerRefinementMaxIterations);
    expect(params.cornerRefinementMinAccuracy, closeTo(cornerRefinementMinAccuracy, 1e-4));
    expect(params.markerBorderBits, markerBorderBits);
    expect(params.perspectiveRemovePixelPerCell, perspectiveRemovePixelPerCell);
    expect(
        params.perspectiveRemoveIgnoredMarginPerCell, closeTo(perspectiveRemoveIgnoredMarginPerCell, 1e-4));
    expect(params.maxErroneousBitsInBorderRate, closeTo(maxErroneousBitsInBorderRate, 1e-4));
    expect(params.minOtsuStdDev, closeTo(minOtsuStdDev, 1e-4));
    expect(params.errorCorrectionRate, closeTo(errorCorrectionRate, 1e-4));
    expect(params.aprilTagQuadDecimate, closeTo(aprilTagQuadDecimate, 1e-4));
    expect(params.aprilTagQuadSigma, closeTo(aprilTagQuadSigma, 1e-4));
    expect(params.aprilTagMinClusterPixels, aprilTagMinClusterPixels);
    expect(params.aprilTagMaxNmaxima, aprilTagMaxNmaxima);
    expect(params.aprilTagCriticalRad, closeTo(aprilTagCriticalRad, 1e-4));
    expect(params.aprilTagMaxLineFitMse, closeTo(aprilTagMaxLineFitMse, 1e-4));
    expect(params.aprilTagMinWhiteBlackDiff, closeTo(aprilTagMinWhiteBlackDiff, 1e-4));
    expect(params.aprilTagDeglitch, aprilTagDeglitch);
    expect(params.detectInvertedMarker, detectInvertedMarker);
    expect(params, isA<cv.ArucoDetectorParameters>());
  });
}
