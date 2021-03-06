//
//  VVJSONSchemaValidator.h
//  VVJSONSchemaValidation
//
//  Created by Vlas Voloshin on 28/12/2014.
//  Copyright (c) 2015 Vlas Voloshin. All rights reserved.
//

#import <Foundation/Foundation.h>

@class VVJSONSchemaFactory;
@class VVJSONSchemaValidationContext;

/**
 Describes an object that can be used to validate a JSON instance.
 @discussion To define a custom validator with one or more keywords assigned to it, create a class that conforms to this protocol and register it with `VVJSONSchema` class using its `+registerValidatorClass:forMetaschemaURI:withError:` method. You don't need to instantiate validators manually - it is done as part of the schema parsing process.
 @warning To ensure thread-safety, all validators must be immutable: do not allow changing their configuration after they are created using `+validatorWithDictionary:schemaFactory:error:` method. Additionally, calling `-subschemas` or `-validateInstance:withError:` methods must have no side-effects on the validator.
 */
@protocol VVJSONSchemaValidator <NSObject>

/** Returns a set of JSON Schema keywords assigned to the receiver. */
+ (NSSet *)assignedKeywords;

/**
 Creates and returns a validator configured using a dictionary containing data from JSON Schema.
 @param schemaDictionary Dictionary of schema properties relevant to the created validator instance.
 @param schemaFactory Factory used to instantiate nested schemas for the validator.
 @param error Error object to contain any error encountered during initialization of the receiver.
 @return Configured validator object, or nil if there was an error during initialization of the instance.
 */
+ (instancetype)validatorWithDictionary:(NSDictionary *)schemaDictionary schemaFactory:(VVJSONSchemaFactory *)schemaFactory error:(NSError * __autoreleasing *)error;

/** Returns an array of all nested schemas used in the receiver. */
- (NSArray *)subschemas;

/**
 Attempts to validate the specified JSON instance.
 @param instance The validated JSON instance.
 @param context Current validation context used for infinite loops detection. Custom validators must pass it to the subschemas' validation method as-is, if necessary; they must otherwise treat this object as an opaque pointer.
 @param error Error object to contain the first encountered validation error.
 @return YES, if validation passed successfully, otherwise NO.
 */
- (BOOL)validateInstance:(id)instance inContext:(VVJSONSchemaValidationContext *)context error:(NSError * __autoreleasing *)error;

@end
