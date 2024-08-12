#pragma once
#include "../Memory/GameData.h"
#include "../SDK/ClientInstance.h"
#include "../Utils/HMath.h"
#include "../Utils/Target.h"
#include "../Utils/Utils.h"
#include "../include/ImGui/imgui.h"

class DrawUtils{

public:
	DrawUtils();
	static void setCtx(GuiData* guiData);
	static void setColor(float r, float g, float b, float a);  // rgba, values from 0 to 1
	static ImVec2 getTextWidth(std::string* textStr, float textSize = 1);
	static ImFont* getFont(int font);

	static void drawTriangle(const Vec2& p1, const ImVec2& p2, const Vec2& p3, ImU32 col, float thickness = 1.0f);
	static void drawNgon(const Vec2& center, float radius, ImU32 col, int num_segments, float thickness = 1.0f);
	static void drawCircle(const Vec2& center, float radius, ImU32 col, int num_segments = 0, float thickness = 1.0f);
	static void drawQuad(const Vec2& p1, const Vec2& p2, const Vec2& p3, const Vec2& p4, ImU32 col, float thickness = 1.0f);
	static void drawLine(const Vec2& p1, const Vec2& p2, ImU32 col, float thickness = 1.0f);  // rgba
	static void drawLinestrip3d(const std::vector<Vec3>& points);
	static void drawLine3d(const Vec3& start, const Vec3& end);
	static void drawBox3d(const Vec3& lower, const Vec3& upper);
	static void fillRectangle(const Vec4& pos, ImU32 col, float alpha);
	static void drawBezierQuadratic(const Vec2& p1, const Vec2& p2, const Vec2& p3, ImU32 col, float thickness, int num_segments);
	static void drawBezierCubic(const Vec2& p1, const Vec2& p2, const Vec2& p3, const Vec2& p4, ImU32 col, float thickness, int num_segments);
	static inline void fillRectangle(const Vec2& start, const Vec2& end) {
		ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(start.x, start.y), ImVec2(end.x, end.y), ImGui::GetColorU32((0,0,0), 1));
	}
	static inline void drawRectangle(const Vec2& start, const Vec2& end, float lineWidth = 1.0f) {
		lineWidth /= 2;
		fillRectangle({ start.x - lineWidth, start.y - lineWidth }, { end.x + lineWidth, start.y + lineWidth });  // TOP
		fillRectangle({ start.x - lineWidth, start.y }, { start.x + lineWidth, end.y });                          // LEFT
		fillRectangle({ end.x - lineWidth, start.y }, { end.x + lineWidth, end.y });                              //
		fillRectangle({ start.x - lineWidth, end.y - lineWidth }, { end.x + lineWidth, end.y + lineWidth });
	}
	static inline void drawRectangle(const Vec4& pos,ImU32 col, float alpha, float lineWidth = 1.0f) {
		lineWidth /= 2;
		fillRectangle(Vec4(pos.x - lineWidth, pos.y - lineWidth, pos.z + lineWidth, pos.y + lineWidth), col, alpha);  // TOP
		fillRectangle(Vec4(pos.x - lineWidth, pos.y, pos.x + lineWidth, pos.w), col, alpha);                          // LEFT
		fillRectangle(Vec4(pos.z - lineWidth, pos.y, pos.z + lineWidth, pos.w), col, alpha);                          //
		fillRectangle(Vec4(pos.x - lineWidth, pos.w - lineWidth, pos.z + lineWidth, pos.w + lineWidth), col, alpha);
	}
	static void drawCircleFilled(const Vec2& center, float radius, ImU32 col, int num_segments = 0);
	static void drawNgonFilled(const Vec2& center, float radius_x, float radius_y, ImU32 col, float rot = 0.0f, int num_segments = 0, float thickness = 1.0f);
	static void drawImage(std::string filePath, const Vec2& p_min, const Vec2& p_max, const Vec2& uv_min = Vec2(0, 0), const Vec2& uv_max = Vec2(1, 1), ImU32 col = IM_COL32_WHITE);
	static void drawImageRounded(std::string filePath, const Vec2& p1, const Vec2& p2, const Vec2& p3, const Vec2& p4, const Vec2& uv1 = Vec2(0, 0), const Vec2& uv2 = Vec2(1, 0), const Vec2& uv3 = Vec2(1, 1), const Vec2& uv4 = Vec2(0, 1), ImU32 col = IM_COL32_WHITE);
	static void drawText(const Vec2& pos, std::string* text,ImU32 color, float alpha = 1, int Font= 0, float textSize=-1);
	static void drawBox(const Vec3& lower, const Vec3& upper, float lineWidth, bool outline = false);
	static void drawEntityBox(Entity* ent, float lineWidth);
	static void draw2D(Entity* ent, float lineWidth);
	static void draw2DCorners(Entity* ent, float lineWidth);
	static void draw2DFill(Entity* ent, ImU32 color, float opacity);
	static void drawNameTags(Entity* ent, float textSize, bool drawHealth = false, bool useUnicodeFont = false);
	//static void drawItem(C_ItemStack* item, const vec2_t& ItemPos, float opacity, float scale, bool isEnchanted);


};

