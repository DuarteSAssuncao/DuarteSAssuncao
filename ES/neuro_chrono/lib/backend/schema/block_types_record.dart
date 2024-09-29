import 'dart:async';

import 'package:collection/collection.dart';

import '/backend/schema/util/firestore_util.dart';
import '/backend/schema/util/schema_util.dart';

import 'index.dart';

class BlockTypesRecord extends FirestoreRecord {
  BlockTypesRecord._(
    super.reference,
    super.data,
  ) {
    _initializeFields();
  }

  // "userId" field.
  String? _userId;
  String get userId => _userId ?? '';
  bool hasUserId() => _userId != null;

  // "name" field.
  String? _name;
  String get name => _name ?? '';
  bool hasName() => _name != null;

  // "color" field.
  Color? _color;
  Color? get color => _color;
  bool hasColor() => _color != null;

  void _initializeFields() {
    _userId = snapshotData['userId'] as String?;
    _name = snapshotData['name'] as String?;
    _color = getSchemaColor(snapshotData['color']);
  }

  static CollectionReference get collection =>
      FirebaseFirestore.instance.collection('blockTypes');

  static Stream<BlockTypesRecord> getDocument(DocumentReference ref) =>
      ref.snapshots().map((s) => BlockTypesRecord.fromSnapshot(s));

  static Future<BlockTypesRecord> getDocumentOnce(DocumentReference ref) =>
      ref.get().then((s) => BlockTypesRecord.fromSnapshot(s));

  static BlockTypesRecord fromSnapshot(DocumentSnapshot snapshot) =>
      BlockTypesRecord._(
        snapshot.reference,
        mapFromFirestore(snapshot.data() as Map<String, dynamic>),
      );

  static BlockTypesRecord getDocumentFromData(
    Map<String, dynamic> data,
    DocumentReference reference,
  ) =>
      BlockTypesRecord._(reference, mapFromFirestore(data));

  @override
  String toString() =>
      'BlockTypesRecord(reference: ${reference.path}, data: $snapshotData)';

  @override
  int get hashCode => reference.path.hashCode;

  @override
  bool operator ==(other) =>
      other is BlockTypesRecord &&
      reference.path.hashCode == other.reference.path.hashCode;
}

Map<String, dynamic> createBlockTypesRecordData({
  String? userId,
  String? name,
  Color? color,
}) {
  final firestoreData = mapToFirestore(
    <String, dynamic>{
      'userId': userId,
      'name': name,
      'color': color,
    }.withoutNulls,
  );

  return firestoreData;
}

class BlockTypesRecordDocumentEquality implements Equality<BlockTypesRecord> {
  const BlockTypesRecordDocumentEquality();

  @override
  bool equals(BlockTypesRecord? e1, BlockTypesRecord? e2) {
    return e1?.userId == e2?.userId &&
        e1?.name == e2?.name &&
        e1?.color == e2?.color;
  }

  @override
  int hash(BlockTypesRecord? e) =>
      const ListEquality().hash([e?.userId, e?.name, e?.color]);

  @override
  bool isValidKey(Object? o) => o is BlockTypesRecord;
}
