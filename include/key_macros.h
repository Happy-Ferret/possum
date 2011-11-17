#ifndef KEY_MACROS_H
#define KEY_MACROS_H

#define _KEY(KEY)    (event.xkey.keycode == KeyCodes->KEY)
#define _MATCH(X)    (event.xkey.keycode & (X))

#define _ALT         Mod1Mask
#define _CTRL        ControlMask
#define _SHIFT       ShiftMask
#define _SUPER       Mod4Mask

#define _ALT_CTRL    (Mod1Mask|ControlMask)
#define _ALT_SHIFT   (Mod1Mask|ShiftMask)
#define _ALT_SUPER   (Mod1Mask|Mod4Mask)

#define _CTRL_ALT    _ALT_CTRL
#define _CTRL_SHIFT  (ShiftMask|ControlMask)
#define _CTRL_SUPER  (Mod4Mask|ControlMask)

#define _SHIFT_ALT   (Mod1Mask|ShiftMask)
#define _SHIFT_CTRL  _CTRL_SHIFT
#define _SHIFT_SUPER (Mod4Mask|ShiftMask)

#define _SUPER_ALT   _ALT_SUPER
#define _SUPER_CTRL  _CTRL_SUPER
#define _SUPER_SHIFT _SHIFT_SUPER


#define ON_KEY(KEY)         if (_KEY(KEY))

#define ON_ALT(KEY)         if (_KEY(KEY) && _ALT)
#define ON_CTRL(KEY)        if (_KEY(KEY) && _CTRL)
#define ON_SHIFT(KEY)       if (_KEY(KEY) && _SHIFT)
#define ON_SUPER(KEY)       if (_KEY(KEY) && _SUPER)

#define ON_ALT_CTRL(KEY)    if (_KEY(KEY) && _ALT_CTRL)
#define ON_ALT_SHIFT(KEY)   if (_KEY(KEY) && _ALT_SHIFT)
#define ON_ALT_SUPER(KEY)   if (_KEY(KEY) && _ALT_SUPER)

#define ON_CTRL_ALT(KEY)    if (_KEY(KEY) && _ALT_CTRL)
#define ON_CTRL_SHIFT(KEY)  if (_KEY(KEY) && _SHIFT_CTRL)
#define ON_CTRL_SUPER(KEY)  if (_KEY(KEY) && _SUPER_CTRL)

#define ON_SHIFT_ALT(KEY)   if (_KEY(KEY) && _ALT_SHIFT)
#define ON_SHIFT_CTRL(KEY)  CTRL_SHIFT(KEY)
#define ON_SHIFT_SUPER(KEY) if (_KEY(KEY) && _SUPER_SHIFT)

#define ON_SUPER_ALT(KEY)   if (_KEY(KEY) && _ALT_SHIFT)
#define ON_SUPER_CTRL(KEY)  CTRL_SUPER(KEY)
#define ON_SUPER_SHIFT(KEY) if (_KEY(KEY) && _SUPER_SHIFT)

#endif
