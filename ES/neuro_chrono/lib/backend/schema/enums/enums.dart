import 'package:collection/collection.dart';

enum BlockType {
  Drink,
  Eat,
  Sleep,
  Work,
  Custom,
}

enum WeekDay {
  Monday,
  Tuesday,
  Wednesday,
  Thursday,
  Friday,
  Saturday,
  Sunday,
}

extension FFEnumExtensions<T extends Enum> on T {
  String serialize() => name;
}

extension FFEnumListExtensions<T extends Enum> on Iterable<T> {
  T? deserialize(String? value) =>
      firstWhereOrNull((e) => e.serialize() == value);
}

T? deserializeEnum<T>(String? value) {
  switch (T) {
    case (BlockType):
      return BlockType.values.deserialize(value) as T?;
    case (WeekDay):
      return WeekDay.values.deserialize(value) as T?;
    default:
      return null;
  }
}
