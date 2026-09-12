#pragma once

namespace Buttons {

using Callback = void (*)();

void begin();
void tick();

void onEnter(Callback cb);
void onDown(Callback cb);
void onUp(Callback cb);
void onHold(Callback cb);

}  // namespace Buttons
