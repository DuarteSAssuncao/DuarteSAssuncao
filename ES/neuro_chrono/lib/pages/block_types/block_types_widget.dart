import '/auth/firebase_auth/auth_util.dart';
import '/backend/backend.dart';
import '/components/block_type_widget.dart';
import '/components/new_block_type_widget.dart';
import '/flutter_flow/flutter_flow_icon_button.dart';
import '/flutter_flow/flutter_flow_theme.dart';
import '/flutter_flow/flutter_flow_util.dart';
import 'package:auto_size_text/auto_size_text.dart';
import 'package:flutter/material.dart';
import 'block_types_model.dart';
export 'block_types_model.dart';

class BlockTypesWidget extends StatefulWidget {
  const BlockTypesWidget({super.key});

  @override
  State<BlockTypesWidget> createState() => _BlockTypesWidgetState();
}

class _BlockTypesWidgetState extends State<BlockTypesWidget> {
  late BlockTypesModel _model;

  final scaffoldKey = GlobalKey<ScaffoldState>();

  @override
  void initState() {
    super.initState();
    _model = createModel(context, () => BlockTypesModel());
  }

  @override
  void dispose() {
    _model.dispose();

    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    return GestureDetector(
      onTap: () => _model.unfocusNode.canRequestFocus
          ? FocusScope.of(context).requestFocus(_model.unfocusNode)
          : FocusScope.of(context).unfocus(),
      child: Scaffold(
        key: scaffoldKey,
        backgroundColor: FlutterFlowTheme.of(context).primaryBackground,
        floatingActionButton: FloatingActionButton(
          onPressed: () {
            print('FloatingActionButton pressed ...');
          },
          backgroundColor: FlutterFlowTheme.of(context).primary,
          elevation: 8.0,
          child: Align(
            alignment: const AlignmentDirectional(1.0, 0.99),
            child: FlutterFlowIconButton(
              borderColor: FlutterFlowTheme.of(context).primary,
              borderRadius: 20.0,
              borderWidth: 0.0,
              buttonSize: 55.0,
              fillColor: FlutterFlowTheme.of(context).primary,
              icon: Icon(
                Icons.add,
                color: FlutterFlowTheme.of(context).secondaryBackground,
                size: 25.0,
              ),
              onPressed: () async {
                await showModalBottomSheet(
                  isScrollControlled: true,
                  backgroundColor: Colors.transparent,
                  enableDrag: false,
                  context: context,
                  builder: (context) {
                    return GestureDetector(
                      onTap: () => _model.unfocusNode.canRequestFocus
                          ? FocusScope.of(context)
                              .requestFocus(_model.unfocusNode)
                          : FocusScope.of(context).unfocus(),
                      child: Padding(
                        padding: MediaQuery.viewInsetsOf(context),
                        child: const NewBlockTypeWidget(),
                      ),
                    );
                  },
                ).then((value) => safeSetState(() {}));
              },
            ),
          ),
        ),
        appBar: AppBar(
          backgroundColor: FlutterFlowTheme.of(context).primary,
          automaticallyImplyLeading: false,
          title: Text(
            'NeuroChrono',
            style: FlutterFlowTheme.of(context).headlineMedium.override(
                  fontFamily: 'OpenDyslexic',
                  color: Colors.white,
                  fontSize: 22.0,
                  letterSpacing: 0.0,
                  useGoogleFonts: false,
                ),
          ),
          actions: [
            Align(
              alignment: const AlignmentDirectional(0.0, 0.0),
              child: Padding(
                padding: const EdgeInsetsDirectional.fromSTEB(0.0, 0.0, 15.0, 0.0),
                child: AutoSizeText(
                  dateTimeFormat(
                    'E, MMM d',
                    getCurrentTimestamp,
                    locale: FFLocalizations.of(context).languageCode,
                  ),
                  textAlign: TextAlign.center,
                  style: FlutterFlowTheme.of(context).headlineMedium.override(
                        fontFamily: 'OpenDyslexic',
                        color: FlutterFlowTheme.of(context).secondaryBackground,
                        fontSize: 22.0,
                        letterSpacing: 0.0,
                        useGoogleFonts: false,
                      ),
                ),
              ),
            ),
          ],
          centerTitle: false,
          elevation: 2.0,
        ),
        body: SafeArea(
          top: true,
          child: StreamBuilder<List<BlockTypesRecord>>(
            stream: queryBlockTypesRecord(
              queryBuilder: (blockTypesRecord) => blockTypesRecord.where(
                'userId',
                isEqualTo: currentUserUid,
              ),
            ),
            builder: (context, snapshot) {
              // Customize what your widget looks like when it's loading.
              if (!snapshot.hasData) {
                return Center(
                  child: SizedBox(
                    width: 50.0,
                    height: 50.0,
                    child: CircularProgressIndicator(
                      valueColor: AlwaysStoppedAnimation<Color>(
                        FlutterFlowTheme.of(context).primary,
                      ),
                    ),
                  ),
                );
              }
              List<BlockTypesRecord> listViewBlockTypesRecordList =
                  snapshot.data!;
              return ListView.builder(
                padding: const EdgeInsets.fromLTRB(
                  0,
                  6.0,
                  0,
                  80.0,
                ),
                scrollDirection: Axis.vertical,
                itemCount: listViewBlockTypesRecordList.length,
                itemBuilder: (context, listViewIndex) {
                  final listViewBlockTypesRecord =
                      listViewBlockTypesRecordList[listViewIndex];
                  return BlockTypeWidget(
                    key: Key(
                        'Keylu9_${listViewIndex}_of_${listViewBlockTypesRecordList.length}'),
                    blockTypeDoc: listViewBlockTypesRecord.reference,
                    name: listViewBlockTypesRecord.name,
                    color: listViewBlockTypesRecord.color!,
                  );
                },
              );
            },
          ),
        ),
      ),
    );
  }
}
