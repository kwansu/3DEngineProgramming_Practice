#pragma once

enum eObj_Message
{
	DEAD, SHOOT
};

class iObjectMessenger
{
	virtual void MessageHandler(iObjectMessenger* pGenerator, eObj_Message eMessage) {}
};