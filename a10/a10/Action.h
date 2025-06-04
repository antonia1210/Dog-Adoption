#pragma once
class Action {
public:
	Action() {}
	virtual ~Action() = default;
	virtual void execute_undo() = 0;
	virtual void execute_redo() = 0;
};