//  HTMLSelector.h
//
//  Public domain. https://github.com/nolanw/HTMLReader

#import <Foundation/Foundation.h>
#import "HTMLElement.h"

/**
 * An HTMLSelector concisely describes a set of nodes.
 *
 * It implements (CSS) Selectors Level 3 http://www.w3.org/TR/css3-selectors/ per the WHATWG HTML spec with the following exceptions:
 *
 * @li The target pseudo-class (:target) is not supported.
 * @li The :lang() and :dir() pseudo-classes are not supported.
 * @li Pseudo-elements (including ::first-line, ::first-leter, ::before, ::after) are not supported.
 * @li The :not() pseudo-class supports any selector. (The spec only supports a simple selector.)
 */
@interface HTMLSelector : NSObject

/**
 * Creates and initializes a new selector.
 */
+ (instancetype)selectorForString:(NSString *)selectorString;

- (instancetype)initWithString:(NSString *)selectorString NS_DESIGNATED_INITIALIZER;

/**
 * A string representation of the selector.
 */
@property (readonly, copy, nonatomic) NSString *string;

/**
 * Whether or not an element is matched by the selector.
 */
- (BOOL)matchesElement:(HTMLElement *)element;

/**
 * The error encountered when parsing the selector string, or nil if there was no error. Errors are in the HTMLSelectorErrorDomain.
 */
@property (readonly, strong, nonatomic) NSError *error;

@end

/**
 * Returns a character set containing all CSS whitespace characters. This is not necessarily identical to `+[NSCharacterSet whitespaceCharacterSet]` or `+[NSCharacterSet whitespaceAndNewlineCharacterSet]`.
 */
extern NSCharacterSet * HTMLSelectorWhitespaceCharacterSet(void);

/**
 * Error domain for all selector parse errors. Errors in this domain describe in localizedFailureReason where in the input the error occurred.
 */
extern NSString * const HTMLSelectorErrorDomain;

/**
 * The corresponding value is an NSString of the input that caused the error.
 */
extern NSString * const HTMLSelectorInputStringErrorKey;

/**
 * The corresponding value is an NSNumber of the 0-based index into the input string at which the parse error occurred.
 */
extern NSString * const HTMLSelectorLocationErrorKey;

/**
 * HTMLSelector expands the HTMLNode class to search for matches.
 */
@interface HTMLNode (HTMLSelector)

/**
 * Returns the nodes matched by selectorString, or nil if the string could not be parsed.
 */
- (NSArray *)nodesMatchingSelector:(NSString *)selectorString;

/**
 * Returns the first node matched by selectorString, or nil if there is no such node or the string could not be parsed.
 */
- (HTMLElement *)firstNodeMatchingSelector:(NSString *)selectorString;

/**
 * Returns the nodes matched by selector.
 */
- (NSArray *)nodesMatchingParsedSelector:(HTMLSelector *)selector;

/**
 * Returns the first node matched by selector, or nil if there is no such node.
 */
- (HTMLElement *)firstNodeMatchingParsedSelector:(HTMLSelector *)selector;

@end

/**
 * HTMLNthExpression represents the expression in an :nth-child (or similar) pseudo-class.
 */
typedef struct {
    
    /**
     * The coefficient.
     */
    NSInteger n;
    
    /**
     * The constant.
     */
    NSInteger c;
} HTMLNthExpression;

/**
 * Returns an initialized HTMLNthExpression.
 *
 * @param n The coefficient.
 * @param c The constant.
 */
extern HTMLNthExpression HTMLNthExpressionMake(NSInteger n, NSInteger c);

/**
 * Returns YES if the two expressions are equal, or NO otherwise.
 */
extern BOOL HTMLNthExpressionEqualToNthExpression(HTMLNthExpression a, HTMLNthExpression b);

/**
 * Translates a string resembling one of the forms `nx + c`, `odd`, or `even` into an HTMLNthExpression `{n, c}`.
 */
extern HTMLNthExpression HTMLNthExpressionFromString(NSString *string);

/**
 * An HTMLNthExpression equivalent to the expression "odd".
 */
extern const HTMLNthExpression HTMLNthExpressionOdd;

/**
 * An HTMLNthExpression equivalent to the expression "even".
 */
extern const HTMLNthExpression HTMLNthExpressionEven;

/**
 * An invalid HTMLNthExpression.
 */
extern const HTMLNthExpression HTMLNthExpressionInvalid;
