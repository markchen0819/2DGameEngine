#include "pch.h"


void Root::Init()
{
	for (Node* n : childNodes)
	{
		n->Init();
	}
}
void Root::Update()
{
	for (Node* n : childNodes)
	{
		n->Update();
	}
}
void Root::Destroy()
{
	std::string s = "Destroy Node: " + Name;
	TraceMessage(s.c_str());
	for (Node* n : childNodes)
	{
		n->Destroy();
		delete n;
		n = nullptr;
	}
	childNodes.clear();
}

void Root::Draw()
{
	for (Node* n : childNodes)
	{
		n->Draw();
	}
}
