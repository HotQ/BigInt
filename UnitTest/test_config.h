#pragma once

#define testInt(ax,bx) Assert::AreEqual(ax==bx,true);
#define testIntS(ax,bx) Assert::AreEqual(ax.string().c_str(),bx);
