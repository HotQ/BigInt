#pragma once

#define testInt(ax,bx) Assert::AreEqual(ax==bx,true);
#define testIntS(ax,bx) Assert::AreEqual(ax.toString().c_str(),bx);
