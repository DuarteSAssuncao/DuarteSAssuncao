import '/auth/firebase_auth/auth_util.dart';
import '/backend/backend.dart';
import '/backend/schema/enums/enums.dart';
import '/flutter_flow/flutter_flow_util.dart';
import '/custom_code/actions/index.dart' as actions;
import '/flutter_flow/custom_functions.dart' as functions;
import 'package:collection/collection.dart';
import 'package:flutter/material.dart';

Future notificationLoop(BuildContext context) async {
  BlocksRecord? thisBlock;
  BlockTypesRecord? thisType;
  BlockTypesRecord? disType;

  while (true) {
    thisBlock = await queryBlocksRecordOnce(
      queryBuilder: (blocksRecord) => blocksRecord
          .where(
            'userId',
            isEqualTo: currentUserUid,
          )
          .where(
            'weekDay',
            isEqualTo: functions.getWeekDay(getCurrentTimestamp).serialize(),
          ),
      singleRecord: true,
    ).then((s) => s.firstOrNull);
    if (thisBlock != null) {
      if (thisBlock.start == functions.dateTimeToInt(getCurrentTimestamp)) {
        thisType = await BlockTypesRecord.getDocumentOnce(thisBlock.type!);
        if (FFAppState().fullScreenNotificationsOn == true) {
          context.pushNamed(
            'Notification',
            queryParameters: {
              'block': serializeParam(
                thisBlock,
                ParamType.Document,
              ),
              'type': serializeParam(
                thisType,
                ParamType.Document,
              ),
              'tasks': serializeParam(
                thisBlock.tasks,
                ParamType.String,
                true,
              ),
            }.withoutNulls,
            extra: <String, dynamic>{
              'block': thisBlock,
              'type': thisType,
            },
          );
        }
        await actions.generateNotification(
          thisType.name,
          'Time to start ${thisType.name} for ${formatNumber(
            thisBlock.duration,
            formatType: FormatType.decimal,
            decimalType: DecimalType.periodDecimal,
          )} minutes!',
        );
        await Future.delayed(const Duration(milliseconds: 60000));
      } else {
        if (functions.timeDifferenceInMinutes(
                functions.calculateEndOfBlock(
                    thisBlock.start, thisBlock.duration),
                functions.dateTimeToInt(getCurrentTimestamp)) ==
            5) {
          disType = await BlockTypesRecord.getDocumentOnce(thisBlock.type!);
          if (FFAppState().fullScreenNotificationsOn == true) {
            context.pushNamed(
              'NotificationEnding',
              queryParameters: {
                'block': serializeParam(
                  thisBlock,
                  ParamType.Document,
                ),
                'type': serializeParam(
                  disType,
                  ParamType.Document,
                ),
                'tasks': serializeParam(
                  thisBlock.tasks,
                  ParamType.String,
                  true,
                ),
              }.withoutNulls,
              extra: <String, dynamic>{
                'block': thisBlock,
                'type': disType,
              },
            );
          }
          await actions.generateNotification(
            disType.name,
            'Ending in 5 minutes',
          );
          await Future.delayed(const Duration(milliseconds: 60000));
        }
      }
    }
    await Future.delayed(const Duration(milliseconds: 6000));
  }
}
