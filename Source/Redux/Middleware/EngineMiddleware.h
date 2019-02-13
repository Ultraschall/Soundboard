#pragma once

#include "../../../JuceLibraryCode/JuceHeader.h"
#include "../Middleware.h"
#include "../../Engine/Engine.h"

class EngineMiddleware : public Middleware {
public:
	EngineMiddleware(Engine &engine);

	ActionObject dispatch(const ActionObject &action, Store &store) override;
	void playerDispatch(const ActionObject & action);
private:
	Engine &engine;
	std::unique_ptr<FileChooser> fileChooser {nullptr};

	void AsyncAddDirectory(Store &store);
	void AsyncAddFile(Store &store);

	class EngineSync : public Timer {
	public:
		EngineSync(Store &store, Engine &engine) : store(store), engine(engine) {}
		void timerCallback() override;
	private:
		Store &store;
		Engine &engine;
	};
	std::unique_ptr<EngineSync> engineSync {nullptr};
};