/**
 @author Contributions from the community; see CONTRIBUTORS.md
 @date 2005-2016
 @copyright MPL2; see LICENSE.txt
*/

#import <Cocoa/Cocoa.h>
#import "DKLayer.h"
#import "DKMetadataItem.h"
#import "DKMetadataStorable.h"

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, DKLayerMetadataSchema) {
	kDKLayerMetadataOriginalSchema NS_SWIFT_NAME(DKLayerMetadataSchema.original) = 1,
	kDKLayerMetadataCaseInsensitiveSchema NS_SWIFT_NAME(DKLayerMetadataSchema.caseInsensitive) = 2,
	kDKLayerMetadata107Schema NS_SWIFT_NAME(DKLayerMetadataSchema.metadata107) = 3
};

/** @brief adds some convenience methods for standard meta data attached to a graphic object.

 adds some convenience methods for standard meta data attached to a graphic object. By default the metadata is just an uncomitted
 <code>id</code>, but using this sets it to be a mutable dictionary. You can then easily get and set values in that dictionary.
*/
@interface DKLayer (Metadata) <DKMetadataStorable>

@property (class) BOOL metadataChangesAreUndoable;

- (void)setupMetadata;
- (nullable NSMutableDictionary<NSString*, DKMetadataItem*>*)metadata NS_REFINED_FOR_SWIFT;
@property (readonly) DKLayerMetadataSchema schema;
@property (readonly, copy, nullable) NSArray<NSString*>* metadataKeys;

- (void)addMetadata:(NSDictionary<NSString*, id>*)dict;
- (void)setMetadata:(NSDictionary<NSString*, DKMetadataItem*>*)dict NS_REFINED_FOR_SWIFT;

- (void)setMetadataItem:(DKMetadataItem*)item forKey:(NSString*)key;
- (nullable DKMetadataItem*)metadataItemForKey:(NSString*)key;
- (void)setMetadataItemValue:(id)value forKey:(NSString*)key;
- (void)setMetadataItemType:(DKMetadataType)type forKey:(NSString*)key;

- (nullable id)metadataObjectForKey:(NSString*)key;

- (BOOL)hasMetadataForKey:(NSString*)key;
- (void)removeMetadataForKey:(nonnull NSString*)key;

- (void)setFloatValue:(CGFloat)val forKey:(NSString*)key;
- (CGFloat)floatValueForKey:(NSString*)key;

- (void)setIntValue:(NSInteger)val forKey:(NSString*)key;
- (NSInteger)intValueForKey:(NSString*)key;

- (void)setString:(NSString*)string forKey:(NSString*)key;
- (nullable NSString*)stringForKey:(NSString*)key;

- (void)setColour:(NSColor*)colour forKey:(NSString*)key;
- (nullable NSColor*)colourForKey:(NSString*)key;

- (void)setSize:(NSSize)size forKey:(NSString*)key;
- (NSSize)sizeForKey:(NSString*)key;

- (void)updateMetadataKeys;
@property (readonly) NSUInteger metadataChecksum;

/** Subclasses that want to prevent access to metadata for a layer can override this to return NO. Controllers that provide
 UI to metadata need to check this - it is not honoured at this level.
 */
@property (readonly) BOOL supportsMetadata;
- (void)metadataWillChangeKey:(nullable NSString*)key;
- (void)metadataDidChangeKey:(nullable NSString*)key;

@end

extern NSString* const kDKLayerMetadataUserInfoKey;
extern NSString* const kDKLayerMetadataUndoableChangesUserDefaultsKey;

@interface DKLayer (MetadataDeprecated)

- (void)setMetadataObject:(null_unspecified id)obj forKey:(null_unspecified id)key DEPRECATED_ATTRIBUTE;

@end

NS_ASSUME_NONNULL_END
