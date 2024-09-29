import 'package:flutter_test/flutter_test.dart';
import 'package:neuro_chrono/flutter_flow/custom_functions.dart';
import 'package:neuro_chrono/backend/schema/enums/enums.dart';
import 'package:fake_cloud_firestore/fake_cloud_firestore.dart';

FakeFirebaseFirestore getInstance() {
  final instance = FakeFirebaseFirestore();
  instance.collection('users').add({
    'createdTime': DateTime.now(),
    'email': "mockup@neurochrono.pt",
    'uid': "mockup",
  });
  instance.collection('blockTypes').add({
    'color': "#ffffff",
    'name': "Mockup A",
    'userId': "mockup",
  });
  instance.collection('blockTypes').add({
    'color': "#000000",
    'name': "Mockup B",
    'userId': "mockup",
  });
  instance.collection('blocks').add({
    'duration': 120,
    'start': 1200,
    'type': instance
        .collection('blockTypes')
        .where('name', isEqualTo: 'Mockup A')
        .get()
        .then((value) => value.docs.first.id),
    'userId': "mockup",
    'weekDay': "Monday",
  });
  return instance;
}

void main() {
  test("Test calculateEndOfBlock", () {
    expect(calculateEndOfBlock(1000, 60), 1100);
    expect(calculateEndOfBlock(1000, 120), 1200);
    expect(calculateEndOfBlock(1000, 180), 1300);
    expect(calculateEndOfBlock(1000, 240), 1400);
    expect(calculateEndOfBlock(0000, 0), 0000);
  });

  test("Test timeDifferenceInMinutes", () {
    expect(timeDifferenceInMinutes(2000, 1900), 60);
    expect(timeDifferenceInMinutes(1000, 0959), 1);
    expect(timeDifferenceInMinutes(2359, 0000), 1439);
    expect(timeDifferenceInMinutes(1438, 1438), 0);
  });

  test("Test stringToWeekDay", () {
    expect(stringToWeekDay('Monday'), WeekDay.Monday);
    expect(stringToWeekDay('Tuesday'), WeekDay.Tuesday);
    expect(stringToWeekDay('Wednesday'), WeekDay.Wednesday);
    expect(stringToWeekDay('Thursday'), WeekDay.Thursday);
    expect(stringToWeekDay('Friday'), WeekDay.Friday);
    expect(stringToWeekDay('Saturday'), WeekDay.Saturday);
    expect(stringToWeekDay('Sunday'), WeekDay.Sunday);
    expect(stringToWeekDay(''), WeekDay.Monday);
  });

  test("Test getWeekDay", () {
    expect(getWeekDay(DateTime(2024, 5, 20)), WeekDay.Monday);
    expect(getWeekDay(DateTime(2024, 5, 21)), WeekDay.Tuesday);
    expect(getWeekDay(DateTime(2024, 5, 22)), WeekDay.Wednesday);
    expect(getWeekDay(DateTime(2024, 5, 23)), WeekDay.Thursday);
    expect(getWeekDay(DateTime(2024, 5, 24)), WeekDay.Friday);
    expect(getWeekDay(DateTime(2024, 5, 25)), WeekDay.Saturday);
    expect(getWeekDay(DateTime(2024, 5, 26)), WeekDay.Sunday);
  });

  test("Test timeToString", () {
    expect(timeToString(0000), "00h00");
    expect(timeToString(0001), "00h01");
    expect(timeToString(0059), "00h59");
    expect(timeToString(0100), "01h00");
    expect(timeToString(1723), "17h23");
    expect(timeToString(2349), "23h49");
    expect(timeToString(2359), "23h59");
  });

  /* test("Test doesIntercept", () {
    final instance = getInstance();
    List<BlocksRecord> blocks = instance
      .collection('blocks')
      .where('userId', isEqualTo: 'mockup')
      .get()
      .then((value) => value.docs.map((doc) => BlocksRecord.fromData(doc.data())).toList());
    expect(doesIntercept(blocks, 1000, 60, WeekDay.Thursday), false);
  }); */
}
