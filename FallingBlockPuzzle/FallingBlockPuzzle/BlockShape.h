//======================================
//      落ち物バズル ブロック形状
//======================================
// ★ここにインクルードガード(開始)を記入してください
//
#ifndef __BLOCKSHAPE_H
#define __BLOCKSHAPE_H



const int SHAPE_WID_MAX = 4;
const int SHAPE_HEI_MAX = 4;

typedef struct {
	int size;
	bool pattern[SHAPE_HEI_MAX][SHAPE_WID_MAX];
} BlockShape;

extern const int blockShapesSize;

// shapeセット
void SetShape(BlockShape* shape, int idx);
// shapeを回転(反時計回り90度)
void RotateShape(BlockShape* shape);
// shapeパターンを設定
void SetShapePattern(BlockShape* shape, int x, int y, bool value);
// shapeパターンを取得
bool GetShapePattern(BlockShape* shape, int x, int y);
// shapeを表示
void PrintShape(BlockShape* shape);

// ★ここにインクルードガード(終了)を記入してください
#endif // !__BLOCKSHAPE_H