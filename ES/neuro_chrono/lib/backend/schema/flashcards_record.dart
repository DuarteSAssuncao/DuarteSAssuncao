import 'dart:async';

import 'package:collection/collection.dart';

import '/backend/schema/util/firestore_util.dart';
import '/backend/schema/util/schema_util.dart';

import 'index.dart';

class FlashcardsRecord extends FirestoreRecord {
  FlashcardsRecord._(
    super.reference,
    super.data,
  ) {
    _initializeFields();
  }

  // "userId" field.
  String? _userId;
  String get userId => _userId ?? '';
  bool hasUserId() => _userId != null;

  // "title" field.
  String? _title;
  String get title => _title ?? '';
  bool hasTitle() => _title != null;

  // "subtitle" field.
  String? _subtitle;
  String get subtitle => _subtitle ?? '';
  bool hasSubtitle() => _subtitle != null;

  // "content" field.
  String? _content;
  String get content => _content ?? '';
  bool hasContent() => _content != null;

  void _initializeFields() {
    _userId = snapshotData['userId'] as String?;
    _title = snapshotData['title'] as String?;
    _subtitle = snapshotData['subtitle'] as String?;
    _content = snapshotData['content'] as String?;
  }

  static CollectionReference get collection =>
      FirebaseFirestore.instance.collection('flashcards');

  static Stream<FlashcardsRecord> getDocument(DocumentReference ref) =>
      ref.snapshots().map((s) => FlashcardsRecord.fromSnapshot(s));

  static Future<FlashcardsRecord> getDocumentOnce(DocumentReference ref) =>
      ref.get().then((s) => FlashcardsRecord.fromSnapshot(s));

  static FlashcardsRecord fromSnapshot(DocumentSnapshot snapshot) =>
      FlashcardsRecord._(
        snapshot.reference,
        mapFromFirestore(snapshot.data() as Map<String, dynamic>),
      );

  static FlashcardsRecord getDocumentFromData(
    Map<String, dynamic> data,
    DocumentReference reference,
  ) =>
      FlashcardsRecord._(reference, mapFromFirestore(data));

  @override
  String toString() =>
      'FlashcardsRecord(reference: ${reference.path}, data: $snapshotData)';

  @override
  int get hashCode => reference.path.hashCode;

  @override
  bool operator ==(other) =>
      other is FlashcardsRecord &&
      reference.path.hashCode == other.reference.path.hashCode;
}

Map<String, dynamic> createFlashcardsRecordData({
  String? userId,
  String? title,
  String? subtitle,
  String? content,
}) {
  final firestoreData = mapToFirestore(
    <String, dynamic>{
      'userId': userId,
      'title': title,
      'subtitle': subtitle,
      'content': content,
    }.withoutNulls,
  );

  return firestoreData;
}

class FlashcardsRecordDocumentEquality implements Equality<FlashcardsRecord> {
  const FlashcardsRecordDocumentEquality();

  @override
  bool equals(FlashcardsRecord? e1, FlashcardsRecord? e2) {
    return e1?.userId == e2?.userId &&
        e1?.title == e2?.title &&
        e1?.subtitle == e2?.subtitle &&
        e1?.content == e2?.content;
  }

  @override
  int hash(FlashcardsRecord? e) =>
      const ListEquality().hash([e?.userId, e?.title, e?.subtitle, e?.content]);

  @override
  bool isValidKey(Object? o) => o is FlashcardsRecord;
}
