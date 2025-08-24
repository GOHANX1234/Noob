#pragma once

#include <string.h>
#include <string>
#include <sstream>
#include <iostream>
#include<sstream>

class Vvector3 {
public:
    float X;
    float Y;
    float Z;
    Vvector3() : X(0), Y(0), Z(0) {}
    Vvector3(float x1, float y1, float z1) : X(x1), Y(y1), Z(z1) {}
    Vvector3(const Vvector3 &v);
    ~Vvector3();
};
Vvector3::Vvector3(const Vvector3 &v) : X(v.X), Y(v.Y), Z(v.Z) {}
Vvector3::~Vvector3() {}


struct Vector2 {
    float x, y;
    Vector2() : x(0), y(0) {}
    Vector2(float _x, float _y) : x(_x), y(_y) {}
};

#define Class_Camera__get_main (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.CoreModule.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Camera"), OBFUSCATE("get_main"))
#define Class_Input__get_touchCount (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.CoreModule.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Input"), OBFUSCATE("get_touchCount"))
#define Class_Input__GetTouch (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.CoreModule.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Input"), OBFUSCATE("GetTouch"), 1)
#define Class_Input__get_mousePosition (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.CoreModule.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Input"), OBFUSCATE("get_mousePosition"))
#define Class_Screen__get_width (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.CoreModule.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Screen"), OBFUSCATE("get_width"))
#define Class_Screen__get_height (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.CoreModule.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Screen"), OBFUSCATE("get_height"))
#define Class_Screen__get_density (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.CoreModule.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Screen"), OBFUSCATE("get_dpi"))
#define Camera_get_fieldOfView (uintptr_t) Il2CppGetMethodOffset("UnityEngine.CoreModule.dll", "UnityEngine", "Camera", "get_fieldOfView")
#define Camera_set_fieldOfView (uintptr_t) Il2CppGetMethodOffset("UnityEngine.CoreModule.dll", "UnityEngine", "Camera", "set_fieldOfView", 1)
#define ForWard (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.CoreModule.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Transform"), OBFUSCATE("get_forward"), 0)
#define Class_Transform__GetPosition Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.CoreModule.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Transform"), OBFUSCATE("get_position_Injected"), 1)
#define Class_Transform__SetPosition Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.CoreModule.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Transform"), OBFUSCATE("set_position_Injected"), 1)
#define Class_Camera__get_main (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.CoreModule.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Camera"), OBFUSCATE("get_main"))
#define Class_Camera__WorldToScreenPoint (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.CoreModule.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Camera"), OBFUSCATE("WorldToScreenPoint"), 1)
#define Class_Component__get_transform (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.CoreModule.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Component"), OBFUSCATE("get_transform"), 0)
#define Class_Transform__get_position (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.CoreModule.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Transform"), OBFUSCATE("get_position"), 0)
#define Class_Transform__Position Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.CoreModule.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Transform"), OBFUSCATE("get_position"), 0)
#define Class_Transform__Rotation Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.CoreModule.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Transform"), OBFUSCATE("get_rotation"), 0)
#define Class_Compent__Transform Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.CoreModule.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Component"), OBFUSCATE("get_transform"), 0)
void *get_main() {
    return reinterpret_cast<void *(__fastcall *)()>(Class_Camera__get_main)();
}
float get_fieldOfView() {
    return reinterpret_cast<float(__fastcall *)(void *)>(Camera_get_fieldOfView)(get_main());
}
void *set_fieldOfView(float value) {
    return reinterpret_cast<void *(__fastcall *)(void *, float)>(Camera_set_fieldOfView)(get_main(), value);
}
static void Transform_INTERNAL_SetPosition(void *player, Vvector3 inn) {
    void (*_SetPosition)(void *, Vvector3) = (void (*)(void *, Vvector3))(Class_Transform__SetPosition);
    _SetPosition(player, inn); 
}

static Quaternion GetRotation(void* player) {
    Quaternion (*_GetRotation)(void* players) = (Quaternion(*)(void *))(Class_Transform__Rotation);
    return _GetRotation(player);
}
/*
static auto get_position_Injected(void *player) {
    auto zero = Vector3::Zero();
    auto (*_get_position_Injected)(void *player, Vector3 *zero) = (void (*)(void *, Vector3 *))(uintptr_t) IL2Cpp::Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.CoreModule.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Transform"), OBFUSCATE("get_position_Injected"), 1);
    _get_position_Injected(player, &zero);
    return zero;
}
static auto set_position_Injected(void *player, Vvector3 position) {
    auto (*_set_position_Injected)(void *player, Vvector3 position) = (void (*)(void *, Vvector3))(uintptr_t) IL2Cpp::Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.CoreModule.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Transform"), OBFUSCATE("set_position_Injected"), 1);
    return _set_position_Injected(player, position);
}*/

#define Class_Camera__WorldToScreenPoint (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.CoreModule.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Camera"), OBFUSCATE("WorldToScreenPoint"), 1)
#define Class_Component__get_transform (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.CoreModule.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Component"), OBFUSCATE("get_transform"), 0)
#define Class_Transform__get_position (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.CoreModule.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Transform"), OBFUSCATE("get_position"), 0)
#define Class_Compent__Transform Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.CoreModule.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Component"), OBFUSCATE("get_transform"), 0)
#define ListPlayer (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Match"), OBFUSCATE("m_Players"))
#define Count (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Match"), OBFUSCATE("GetPlayerCount"))
#define EnemyUpdate (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("LateUpdate"), 0)
#define MainCam (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("MainCameraTransform"))
#define Match (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("GameFacade"), OBFUSCATE("CurrentMatch"), 0)
#define Local (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Match"), OBFUSCATE("m_LocalPlayer"))
#define Visible (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("IsVisible"), 0)
#define Team (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("IsLocalTeammate"), 1)
#define Die (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("get_IsDieing"), 0)
#define CurHP (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("get_CurHP"), 0)
#define MaxHP (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("get_MaxHP"), 0)
#define Name (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("get_NickName"), 0)
#define Aim (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("SetAimRotation"), 2)
#define Scope (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("get_IsSighting"),0 )
#define Fire (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("IsFiring"), 0)
#define LocalBool (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("IsLocalPlayer"), 0)
#define CarLocal (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("VehicleIAmIn"), 0)
#define GetCar (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("get_IsDriver"), 0)
#define Head (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("GetHeadTF"), 0)
#define ForWard (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.CoreModule.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Transform"), OBFUSCATE("get_forward"), 0)
#define Report1 (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("InteractionPopUtil"), OBFUSCATE("CreateReportPlayer"), 3)
#define Report2 (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("UIHudMatchResultItemBaseController"), OBFUSCATE("SetReportData"), 4)
#define Report3 (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("UIModelVoice"), OBFUSCATE("get_ReportedPlayerTimeDict"), 0)
#define Report4 (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("InteractionPopUtil"), OBFUSCATE("CreateAddToBlackList"), 3)
#define CharGet (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("mscorlib.dll"), OBFUSCATE("System"), OBFUSCATE("String"), OBFUSCATE("get_Chars"), 1)
#define Raycast (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("PhysicsUtil"), OBFUSCATE("SingleLineCheck"), 4)
#define HeadColider (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("get_HeadCollider"), 0)
#define Time (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.CoreModule.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Time"), OBFUSCATE("get_deltaTime"), 0)
#define Floding (uintptr_t)Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("IsFoldWingGliding"), 0)
#define Running (uintptr_t)Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("message"), OBFUSCATE("ProtoUtil"), OBFUSCATE("MappingFromPhysXState"), 1)
static bool get_isLocalTeam(void* player) {
    if (!player || !Team) return false;
    using IsLocalTeammateFn = bool(*)(void*, bool);
    return ((IsLocalTeammateFn)Team)(player, true);
}
static void* Player_GetHeadCollider(void* player) {
    using HeadColliderFn = void*(*)(void*);
    return ((HeadColliderFn)HeadColider)(player);
}
void* GetLocalPlayer(void* match) {
    if (!match) return nullptr;
    return *(void**)((uintptr_t)match + Local);
}
static void* GetPlayers(void* matchInstance) {
    using GetPlayersFn = void*(*)(void*);
    return ((GetPlayersFn)ListPlayer)(matchInstance);
}
static Vector3 Transform_GetPosition(void* player) {
    Vector3 out = Vector3::zero();
    using GetPositionFn = void(*)(void*, Vector3*);
    ((GetPositionFn)Class_Transform__GetPosition)(player, &out);
    return out;
}
static void* Curent_Match() {
    using MatchFn = void*(*)(void*);
    return ((MatchFn)Match)(nullptr);
}
static void* GetHeadPositions(void* player) {
    using GetHeadFn = void*(*)(void*);
    return ((GetHeadFn)Head)(player);
}
Vector3 get_position(void* player) {
    using GetPosFn = Vector3(*)(void*);
    return ((GetPosFn)Class_Transform__Position)(player);
}
static void* Component_GetTransform(void* player) {
    using GetTransformFn = void*(*)(void*);
    return ((GetTransformFn)Class_Compent__Transform)(player);
}

static Vector3 WorldToScreenPoint(void* camera, Vector3 worldPos) {
    using W2SFn = Vector3(*)(void*, Vector3);
    return ((W2SFn)Class_Camera__WorldToScreenPoint)(camera, worldPos);
}
static void* Camera_main() {
    using CameraFn = void*(*)(void*);
    return ((CameraFn)Class_Camera__get_main)(nullptr);
}

static bool get_isVisible(void* player) {
    using VisibleFn = bool(*)(void*);
    return ((VisibleFn)Visible)(player);
}

static bool get_IsDieing(void* player) {
    using IsDyingFn = bool(*)(void*);
    return ((IsDyingFn)Die)(player);
}

static int GetHp(void* player) {
    using GetHpFn = int(*)(void*);
    return ((GetHpFn)CurHP)(player);
}

static int get_MaxHP(void* player) {
    using MaxHpFn = int(*)(void*);
    return ((MaxHpFn)MaxHP)(player);
}

static monoString* get_NickName(void* player) {
    using NickFn = monoString*(*)(void*);
    return ((NickFn)Name)(player);
}

static Vector3 GetForward(void* player) {
    using ForwardFn = Vector3(*)(void*);
    return ((ForwardFn)ForWard)(player);
}

static bool IsLocal(void* player) {
    using IsLocalFn = bool(*)(void*);
    return ((IsLocalFn)LocalBool)(player);
}

static void* GetLocalCar(void* player) {
    using LocalCarFn = void*(*)(void*);
    return ((LocalCarFn)CarLocal)(player);
}

static bool IsDriver(void* player) {
    using DriverFn = bool(*)(void*);
    return ((DriverFn)GetCar)(player);
}
static void set_aim(void* player, Quaternion look) {
    using AimFn = void(*)(void*, Quaternion, bool);
    ((AimFn)Aim)(player, look, false);  
}
char get_Chars(monoString* str, int index) {
    using CharGetFn = char(*)(monoString*, int);
    return ((CharGetFn)CharGet)(str, index);
}
static bool get_IsSighting(void* player) {
    using SightFn = bool(*)(void*);
    return ((SightFn)Scope)(player);
}
static bool get_IsFiring(void* player) {
    using FireFn = bool(*)(void*);
    return ((FireFn)Fire)(player);
}
static bool Physics_Raycast(Vector3 camLocation, Vector3 headLocation, unsigned int layerID, void* collider) {
    using RaycastFn = bool(*)(Vector3, Vector3, unsigned int, void*);
    return ((RaycastFn)Raycast)(camLocation, headLocation, layerID, collider);
}
Vector3 getPosition(void* transform) {
    return get_position(Component_GetTransform(transform));
}
static Vector3 GetHeadPosition(void* player) {
    return get_position(GetHeadPositions(player));
}
static Vector3 CameraMain(void* player) {
    return get_position(*(void**)((uintptr_t)player + MainCam));
}

int get_width() {
    return reinterpret_cast<int(__fastcall*)()>(Class_Screen__get_width)();
}
int get_height() {
    return reinterpret_cast<int(__fastcall*)()>(Class_Screen__get_height)();
}
float get_density() {
    return reinterpret_cast<float(__fastcall*)()>(Class_Screen__get_density)();
}
