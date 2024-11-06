#pragma once

enum class ColliderType
{
	Point,
	Circle,
	Rectangle
};

enum class KeyState
{
	KeyUp,
	KeyDown,
	KeyPressed,
	KeyNone
};
enum class KeyCode
{
	W = 0,
	A,
	S,
	D,
	Space,
	MouseLeftButton,
	MouseRightButton,
	//MiddleButton,

	end
};

enum class SceneIds
{
	None = -1,
	SceneDev1,
	SceneDev2,
	Count,
};

enum class Origins
{
	TopLeft, TopCenter, TopRight,
	MiddleLeft, MiddleCenter, MiddleRight,
	BottomLeft, BottomCenter, BottomRight,
	Custom
};


enum class LayerType
{
	Default,

	Player,
	Enemy,
	PlayerBullet,
	EnemyBullet,

	InGameUI,

	UI,
	End
};

enum class ColliderLayer
{
	Default,
	Player,
	Enemy,
	PlayerBullet,
	EnemyBullet,


	End
};

enum class CameraType
{
	Main,
	Effet,
	UI,

	End
};