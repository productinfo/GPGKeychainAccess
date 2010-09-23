/*
 Copyright © Roman Zechmeister, 2010
 
 Dieses Programm ist freie Software. Sie können es unter den Bedingungen 
 der GNU General Public License, wie von der Free Software Foundation 
 veröffentlicht, weitergeben und/oder modifizieren, entweder gemäß 
 Version 3 der Lizenz oder (nach Ihrer Option) jeder späteren Version.
 
 Die Veröffentlichung dieses Programms erfolgt in der Hoffnung, daß es Ihnen 
 von Nutzen sein wird, aber ohne irgendeine Garantie, sogar ohne die implizite 
 Garantie der Marktreife oder der Verwendbarkeit für einen bestimmten Zweck. 
 Details finden Sie in der GNU General Public License.
 
 Sie sollten ein Exemplar der GNU General Public License zusammen mit diesem 
 Programm erhalten haben. Falls nicht, siehe <http://www.gnu.org/licenses/>.
*/

enum {
	RunCmdNoKeyserverFound = 501, //Es wurde kein Schlüsselserver festgelegt.
	RunCmdIllegalProtocolType = 502,
	RunCmdNoKeyserverHelperFound = 503
} RunCmdReturnValue;

enum {
	RunServerCommandSearch,
	RunServerCommandSend,
	RunServerCommandGet
} RunServerCommandType;

@class SheetController;
@class KeyInfo;
@class KeyInfo_Subkey;

@interface ActionController : NSWindowController {
    IBOutlet NSTreeController *keysController;
    IBOutlet NSArrayController *signaturesController;
    IBOutlet NSArrayController *subkeysController;
    IBOutlet NSArrayController *userIDsController;
	IBOutlet NSView *exportKeyOptionsView;

	
	BOOL allowSecretKeyExport;
	BOOL useASCIIForExport;
}
@property BOOL allowSecretKeyExport;
@property BOOL useASCIIForExport;

- (IBAction)exportKey:(id)sender;
- (IBAction)importKey:(id)sender;
- (IBAction)addSignature:(id)sender;
- (IBAction)addSubkey:(NSButton *)sender;
- (IBAction)addUserID:(NSButton *)sender;
- (IBAction)changeExpirationDate:(NSButton *)sender;
- (IBAction)changePassphrase:(NSButton *)sender;
- (IBAction)removeSignature:(NSButton *)sender;
- (IBAction)removeSubkey:(NSButton *)sender;
- (IBAction)removeUserID:(NSButton *)sender;
- (IBAction)revokeSignature:(NSButton *)sender;
- (IBAction)revokeSubkey:(NSButton *)sender;
- (IBAction)setDisabled:(NSButton *)sender;
- (IBAction)setPhoto:(NSImageView *)sender;
- (IBAction)setPrimaryUserID:(NSButton *)sender;
- (IBAction)setTrsut:(NSPopUpButton *)sender;
- (IBAction)generateNewKey:(id)sender;
- (IBAction)deleteKey:(id)sender;
- (void)exportKeys:(NSSet *)keys toFile:(NSString *)path armored:(BOOL)armored allowSecret:(BOOL)allowSec;
- (void)importFromFiles:(NSArray *)files;
- (IBAction)sendKeysToServer:(id)sender;
- (IBAction)searchKeys:(id)sender;
- (IBAction)receiveKeys:(id)sender;
- (IBAction)refreshKeysFromServer:(id)sender;


- (void)generateNewKeyWithName:(NSString *)name email:(NSString *)email comment:(NSString *)comment type:(NSInteger)type length:(NSInteger)length daysToExpire:(NSInteger)daysToExpire;
- (void)addSubkeyForKeyInfo:(KeyInfo *)keyInfo type:(NSInteger)type length:(NSInteger)length daysToExpire:(NSInteger)daysToExpire;
- (void)addUserIDForKeyInfo:(KeyInfo *)keyInfo name:(NSString *)name email:(NSString *)email comment:(NSString *)comment;
- (void)addSignatureForKeyInfo:(KeyInfo *)keyInfo andUserID:(NSString *)userID signKey:(NSString *)signFingerprint type:(NSInteger)type local:(BOOL)local daysToExpire:(NSInteger)daysToExpire;
- (void)changeExpirationDateForKeyInfo:(KeyInfo *)keyInfo subkey:(KeyInfo_Subkey *)subkey daysToExpire:(NSInteger)daysToExpire;
- (NSString *)searchKeysWithPattern:(NSString *)pattern;
- (void)receiveKeysWithPattern:(NSString *)pattern;






int runCommandWithArray(NSString *command, NSString *inText, NSData **outData, NSData **errData, NSArray *arguments);
int runGPGCommandWithArray(NSString *inText, NSData **outData, NSData **errData, NSArray *args, BOOL batchMode);
int runGPGCommand(NSString *inText, NSString **outText, NSString **errText, NSString *firstArg, ...) NS_REQUIRES_NIL_TERMINATION;
int searchKeysOnServer(NSString *searchPattern, NSString **outText);


NSInteger getIndexForUserID(NSString *fingerprint, NSString *userID);
NSInteger getIndexForSubkey(NSString *fingerprint, NSString *keyID);

//NSString* unescape(NSString *string, NSString *escapeString);

@end