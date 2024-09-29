import 'dart:convert';
import 'dart:math' as math;

import 'package:flutter/material.dart';
import 'package:google_fonts/google_fonts.dart';
import 'package:intl/intl.dart';
import 'package:timeago/timeago.dart' as timeago;
import 'lat_lng.dart';
import 'place.dart';
import 'uploaded_file.dart';
import '/backend/backend.dart';
import 'package:cloud_firestore/cloud_firestore.dart';
import '/backend/schema/enums/enums.dart';
import '/auth/firebase_auth/auth_util.dart';

WeekDay stringToWeekDay(String weekDay) {
  switch (weekDay) {
    case 'Monday':
      return WeekDay.Monday;
    case 'Tuesday':
      return WeekDay.Tuesday;
    case 'Wednesday':
      return WeekDay.Wednesday;
    case 'Thursday':
      return WeekDay.Thursday;
    case 'Friday':
      return WeekDay.Friday;
    case 'Saturday':
      return WeekDay.Saturday;
    case 'Sunday':
      return WeekDay.Sunday;
    default:
      return WeekDay.Monday;
  }
}

int calculateEndOfBlock(
  int start,
  int dur,
) {
  int sHour = (start ~/ 100) + (dur ~/ 60);
  int sMin = (start % 100) + (dur % 60);
  int end = (sHour * 100) + ((sMin ~/ 60) * 100 + (sMin % 60));
  return end;
}

WeekDay getWeekDay(DateTime now) {
  switch (now.weekday) {
    case 1:
      return WeekDay.Monday;
    case 2:
      return WeekDay.Tuesday;
    case 3:
      return WeekDay.Wednesday;
    case 4:
      return WeekDay.Thursday;
    case 5:
      return WeekDay.Friday;
    case 6:
      return WeekDay.Saturday;
    case 7:
      return WeekDay.Sunday;
    default:
      return WeekDay.Monday;
  }
}

int dateTimeToInt(DateTime dt) {
  return (dt.hour * 100) + dt.minute;
}

String timeToString(int time) {
  var f = NumberFormat("00");
  return (f.format(time ~/ 100)).toString() +
      'h' +
      (f.format(time % 100)).toString();
}

bool doesIntercept(
  List<BlocksRecord> blocks,
  int start,
  int dur,
  WeekDay? weekday,
) {
  if (weekday == null) return false;

  for (BlocksRecord b in blocks) {
    if (b.weekDay != weekday) continue;
    if (b.start == start) return true;
    if (b.start < start && calculateEndOfBlock(b.start, b.duration) > start)
      return true;
    if (start < b.start && calculateEndOfBlock(start, dur) > b.start)
      return true;
  }

  return false;
}

DateTime? intToDatetime(int startingTime) {
  DateTime n = new DateTime.now();
  return DateTime(
      n.year, n.month, n.day, startingTime ~/ 100, startingTime % 100);
}

int datetimeToUnixTimestamp(DateTime datetime) {
  return datetime.toUtc().millisecondsSinceEpoch ~/ 1000;
}

int timeDifferenceInMinutes(
  int a,
  int b,
) {
  return (a ~/ 100 - b ~/ 100) * 60 + ((a % 100) % 60) - ((b % 100) % 60);
}

Color colorToTertiary(Color primaryColor) {
  final HSLColor hslColor = HSLColor.fromColor(primaryColor);
  final double adjustedHue = (hslColor.hue + 180) % 360;
  final Color tertiaryColor = HSLColor.fromAHSL(
    1.0,
    adjustedHue,
    hslColor.saturation,
    hslColor.lightness,
  ).toColor();
  return tertiaryColor;
}

Color colorToSecondary(Color primaryColor) {
  HSLColor hsl = HSLColor.fromColor(primaryColor);
  double ligthness =
      (hsl.lightness + (hsl.lightness > 0.5 ? -0.2 : 0.2)).clamp(0.0, 1.0);
  return HSLColor.fromAHSL(
          primaryColor.opacity, hsl.hue, hsl.saturation, ligthness)
      .toColor();
}

Color colorToGrayScale(Color color) {
  final val = (color.computeLuminance() * 255).round();
  return Color.fromARGB(color.alpha, val, val, val);
}

Color colorToInverse(Color color) {
  return Color.fromARGB(
      color.alpha, 255 - color.red, 255 - color.green, 255 - color.blue);
}

int colorGrayScaleValue(Color color) {
  return colorToGrayScale(color).red;
}
