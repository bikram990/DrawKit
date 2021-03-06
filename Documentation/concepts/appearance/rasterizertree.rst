`DKStyle` and the Rasterizer Tree
---------------------------------

Actual pixels on screen (or in printed output) are generated by `DKRasterizers`. These objects take the geometric path supplied by an object and use it to draw things, for example strokes and fills, to give them a visible presence. `DKRasterizer` is a semi-abstract base class for all rasterizers - concrete subclasses include `DKStroke` and `DKFill` among numerous others. Rasterizers are not limited to using the exact path they are given - they can use modified versions of it for special effects, and so forth.

Rasterizers are organised into a tree, just like layers and drawables. `DKRastGroup` is a `DKRasterizer` that can contain other rasterizers. Each rasterizer is applied to the path in turn, so the order of rasterizers gives different effects - those that drawn last draw "on top" of those that drew earlier. Again this is done for maximum flexibility - the decision about drawing order is up to you, simply by arranging the rasterizers in the desired order.

`DKStyle` is a subclass of `DKRastGroup` (just as `DKDrawing` is a subclass of `DKLayerGroup`). A style is a high-level object that can be attached directly to `DKDrawableObjects` to render that object's appearance. Where `DKRastGroup` is merely a collection of rasterizers, `DKStyle` brings several additional powerful behaviours into the picture. The main properties of a style are:

* Its list of rasterizers - these do the actual work of rendering a path.
* The style's name - this is something generally for a user interface's benefit.
* Whether the style is sharable or not (see below).
* Whether the style is locked or not (editable).
* The style's unique ID - this is used to identify a style across time, space and different documents.
* Any text attributes
* Managing undo for all properties of all contained rasterizers.

The ability to share styles among several objects can be very useful. Some applications might want to do this a lot, for example a GIS application where a style is used to set the appearance of every symbol of a certain kind. Other applications won't want to do this, for example a simple drawing application might prefer to stick to having a 1:1 relationship between an object and its style. DrawKit supports it whichever way you prefer, or allows you to mix the two approaches if you wish. A style is set to be sharable or not - the initial state of this flag is taken from a class variable so you can set the default for all new styles just once.

A style is always copied when it is attached to an object, but the sharable flag affects copying. If sharable, the object is not really copied, but simply retained. Non-sharable styles are genuinely copied. Thus shared styles, if changed, will change all objects to which they are attached at once, whereas non-shared ones only affect the single object they belong to. Style sharing works even when a style is copied and pasted from one object to another - if a sharable style, it will be shared with the object to which it is pasted. Note that style sharability is a property of the style itself, not the object(s) to which the style is attached.

All properties of all rasterizers contained by a style are undoable. Because there are so many possible properties that can change and each rasterizer doesn't really want to be bogged down worrying about how to deal with undo, `DKStyle` makes use of Key-Value Observing (KVO) to implement undo. Each rasterizer advertises the properties that can be undone in a class method, and the style uses that information to observe changes to those properties via KVO. It then saves the old properties to the undo manager so they can be undone.

Note there is no limit to the number or type of rasterizers that a style can contain. If your style wants twenty different strokes there's no reason (except performance, possibly) why it couldn't. It is the ability to superimpose and reorder rasterizers freely that give styles their tremendous versatility.
