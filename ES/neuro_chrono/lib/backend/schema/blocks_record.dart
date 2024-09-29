import 'dart:async';

import 'package:collection/collection.dart';

import '/backend/schema/util/firestore_util.dart';
import '/backend/schema/util/schema_util.dart';
import '/backend/schema/enums/enums.dart';

import 'index.dart';
import '/flutter_flow/flutter_flow_util.dart';

class BlocksRecord extends FirestoreRecord {
  BlocksRecord._(
    super.reference,
    super.data,
  ) {
    _initializeFields();
  }

  // "weekDay" field.
  WeekDay? _weekDay;
  WeekDay? get weekDay => _weekDay;
  bool hasWeekDay() => _weekDay != null;

  // "duration" field.
  int? _duration;
  int get duration => _duration ?? 0;
  bool hasDuration() => _duration != null;

  // "userId" field.
  String? _userId;
  String get userId => _userId ?? '';
  bool hasUserId() => _userId != null;

  // "start" field.
  int? _start;
  int get start => _start ?? 0;
  bool hasStart() => _start != null;

  // "type" field.
  DocumentReference? _type;
  DocumentReference? get type => _type;
  bool hasType() => _type != null;

  // "tasks" field.
  List<String>? _tasks;
  List<String> get tasks => _tasks ?? const [];
  bool hasTasks() => _tasks != null;

  void _initializeFields() {
    _weekDay = deserializeEnum<WeekDay>(snapshotData['weekDay']);
    _duration = castToType<int>(snapshotData['duration']);
    _userId = snapshotData['userId'] as String?;
    _start = castToType<int>(snapshotData['start']);
    _type = snapshotData['type'] as DocumentReference?;
    _tasks = getDataList(snapshotData['tasks']);
  }

  static CollectionReference get collection =>
      FirebaseFirestore.instance.collection('blocks');

  static Stream<BlocksRecord> getDocument(DocumentReference ref) =>
      ref.snapshots().map((s) => BlocksRecord.fromSnapshot(s));

  static Future<BlocksRecord> getDocumentOnce(DocumentReference ref) =>
      ref.get().then((s) => BlocksRecord.fromSnapshot(s));

  static BlocksRecord fromSnapshot(DocumentSnapshot snapshot) => BlocksRecord._(
        snapshot.reference,
        mapFromFirestore(snapshot.data() as Map<String, dynamic>),
      );

  static BlocksRecord getDocumentFromData(
    Map<String, dynamic> data,
    DocumentReference reference,
  ) =>
      BlocksRecord._(reference, mapFromFirestore(data));

  @override
  String toString() =>
      'BlocksRecord(reference: ${reference.path}, data: $snapshotData)';

  @override
  int get hashCode => reference.path.hashCode;

  @override
  bool operator ==(other) =>
      other is BlocksRecord &&
      reference.path.hashCode == other.reference.path.hashCode;
}

Map<String, dynamic> createBlocksRecordData({
  WeekDay? weekDay,
  int? duration,
  String? userId,
  int? start,
  DocumentReference? type,
}) {
  final firestoreData = mapToFirestore(
    <String, dynamic>{
      'weekDay': weekDay,
      'duration': duration,
      'userId': userId,
      'start': start,
      'type': type,
    }.withoutNulls,
  );

  return firestoreData;
}

class BlocksRecordDocumentEquality implements Equality<BlocksRecord> {
  const BlocksRecordDocumentEquality();

  @override
  bool equals(BlocksRecord? e1, BlocksRecord? e2) {
    const listEquality = ListEquality();
    return e1?.weekDay == e2?.weekDay &&
        e1?.duration == e2?.duration &&
        e1?.userId == e2?.userId &&
        e1?.start == e2?.start &&
        e1?.type == e2?.type &&
        listEquality.equals(e1?.tasks, e2?.tasks);
  }

  @override
  int hash(BlocksRecord? e) => const ListEquality()
      .hash([e?.weekDay, e?.duration, e?.userId, e?.start, e?.type, e?.tasks]);

  @override
  bool isValidKey(Object? o) => o is BlocksRecord;
}
