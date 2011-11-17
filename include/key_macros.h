#ifndef KEY_MACROS_H
#define KEY_MACROS_H

#define _ALT         Mod1Mask
#define _CTRL        ControlMask
#define _SHIFT       ShiftMask
#define _SUPER       Mod4Mask

#define _ALT_CTRL    (_ALT|_CTRL)
#define _ALT_SHIFT   (_ALT|_SHIFT)
#define _ALT_SUPER   (_ALT|_SUPER)

#define _CTRL_ALT    _ALT_CTRL
#define _CTRL_SHIFT  (_SHIFT|_CTRL)
#define _CTRL_SUPER  (_SUPER|_CTRL)

#define _SHIFT_ALT   (Mod1Mask|ShiftMask)
#define _SHIFT_CTRL  _CTRL_SHIFT
#define _SHIFT_SUPER (Mod4Mask|ShiftMask)

#define _SUPER_ALT   _ALT_SUPER
#define _SUPER_CTRL  _CTRL_SUPER
#define _SUPER_SHIFT _SHIFT_SUPER



#define _KEY(KEY)            (event.xkey.keycode == KeyCodes->KEY)
//#define ON_KEY(KEY)          if (_KEY(KEY))
#define ON(KEY, MOD)         if (_KEY(KEY) && (event.xkey.state & (MOD)))


#define ON_ALT(KEY)          ON(KEY, _ALT)
#define ON_CTRL(KEY)         ON(KEY, _CTRL)
#define ON_SHIFT(KEY)        ON(KEY, _SHIFT)
#define ON_SUPER(KEY)        ON(KEY, _SUPER)

#define ON_ALT_CTRL(KEY)     ON(KEY, _ALT_CTRL)
#define ON_ALT_SHIFT(KEY)    ON(KEY, _ALT_SHIFT)
#define ON_ALT_SUPER(KEY)    ON(KEY, _ALT_SUPER)

#define ON_CTRL_ALT(KEY)     ON_ALT_CTRL(KEY)
#define ON_CTRL_SHIFT(KEY)   ON(KEY, _SHIFT_CTRL)
#define ON_CTRL_SUPER(KEY)   ON(KEY, _SUPER_CTRL)

#define ON_SHIFT_ALT(KEY)    ON(KEY, _ALT_SHIFT)
#define ON_SHIFT_CTRL(KEY)   ON_CTRL_SHIFT(KEY)
#define ON_SHIFT_SUPER(KEY)  ON(KEY, _SUPER_SHIFT)

#define ON_SUPER_ALT(KEY)    ON(KEY, _ALT_SHIFT)
#define ON_SUPER_CTRL(KEY)   ON_CTRL_SUPER(KEY)
#define ON_SUPER_SHIFT(KEY)  ON(KEY, _SUPER_SHIFT)

#endif
