#include "Tracer.h"
#include "../../DrawUtils.h"

Tracer::Tracer() : IModule(0x0, Category::VISUAL, "Draws lines to ESP highlighted entities.") {
	registerIntSetting("Red", &red, red, 0, 255);
	registerIntSetting("Green", &green, green, 0, 255);
	registerIntSetting("Blue", &blue, blue, 0, 255);
}


Tracer::~Tracer()
{
}

std::string Tracer::getModuleName(){
return "Tracer";
}
std::shared_ptr<glmatrixf> refdef2;
void Tracer::onPreRender(){
	glmatrixf* badrefdef = Game.getClientInstance()->getRefDef();
	refdef2 = std::shared_ptr<glmatrixf>(badrefdef->correct());

	Game.forEachEntity([&](Entity* ent, bool valid) {
		if (Target::isValidTarget(ent) && Game.canUseMoveKeys()) {
			Vec2 target;
			Vec2 screenSize(Game.getGuiData()->widthGame, Game.getGuiData()->heightGame);
			refdef2->OWorldToScreen(Game.getClientInstance()->levelRenderer->getOrigin(), *ent->getPos(), target, Game.getClientInstance()->getFov(), screenSize);
			Vec2 mid((screenSize.x / 2), (screenSize.y / 2));
			if (target != Vec2(0, 0)) {
				DrawUtils::setColor(red / 255.f, green / 255.f, blue / 255.f, 1);
				DrawUtils::drawLine(mid, target, ImColor(), 0.2f);
			}
		}
		});
}
