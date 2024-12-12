// MiniCLex.cs                                              HDO, 2006-08-28
// -------------
// Lexical analyzer (finite-state machine interpreter).
// Generated by Coco-2 (SG).
//=====================================|========================================

using System;
using System.Collections;
using System.Collections.Specialized;
using System.IO;

public class MiniCLex {

  public const String MODULENAME = "MiniCLex";
  public const int    EOFSPIX    = 1;

  public static TextReader src;

  // --- token information ---
  public static int    token;               // current token
  public static int    tokenLine, tokenCol; // position of current token
  public static String tokenStr;            // token string recognized

  // --- current char. info, for "power users" only ---
  public static char   curCh;               // current input character
  public static int    curLine, curCol;     // position of curCh


  public static void MiniCLexMethod(Utils.ModuleAction action, out String moduleName) {
  //-----------------------------------|----------------------------------------
    moduleName = MODULENAME;
    switch (action) {
      case Utils.ModuleAction.getModuleName:
        return;
      case Utils.ModuleAction.initModule:
        caseSensitive = true;
        lt            = new LexicalTable();
        tokenStrArr   = new char[256];
        kwHt          = CreateHashtable();
        nHt           = CreateHashtable();
        nl            = new ArrayList();
        break;
      case Utils.ModuleAction.resetModule:
        kwHt.Clear();
        nHt.Clear();
        nl.Clear();
        break;
      case Utils.ModuleAction.cleanupModule:
        lt            = null;
        tokenStrArr   = null;
        kwHt          = null;
        nHt           = null;
        nl            = null;
        break;
    } // switch
  } // MiniCLexMethod

  private static  Hashtable CreateHashtable() {
    if (caseSensitive)
      return new Hashtable();
    else
      return CollectionsUtil.CreateCaseInsensitiveHashtable();
  } // CreateHashtable


  public static void InitLex() {
  //-----------------------------------|----------------------------------------
    // --- initialize keyword hash table  ---
    kwHt.Clear();
    EnterKeyword(  1, "int");
    EnterKeyword(  2, "main");
    EnterKeyword(  3, "printf");
    EnterKeyword(  4, "scanf");
    EnterKeyword(  5, "void");
    // --- initialize name data structures  ---
    nHt.Clear();
    nl.Clear();
    nl.Add("");      // so spix = 0 is the empty string
    nl.Add("!EOF!"); // so EOFSPIX = 1
    // --- (re)set global data ---
    curLineStr  = "";
    curCh       = ' ';
    curLine     = 0;
    curCol      = 2;
    tokenStr    = null;
    token       = 0;
    tokenCol    = 0;
    tokenLine   = 0;
    tokenStrLen = 0;
    pendingEOLs = 0;
    apxLen      = pendingEOLs; // to prevent warning
  } // InitLex

  private static void EnterKeyword(int token, String keyword) {
    kwHt.Add(keyword, token);
  } // EnterKeyword


  // *** start of global LEX declarations from ATG ***
  
  // *** end of global LEX declarations from ATG ***


  public static bool caseSensitive;

  private class LexicalTable {
    public int   header = 4;
    public int[] startTab = {
          0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
          0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
          0,  0,  0,  0,  0,  0,  0,  0,  6,  7,  4,  2,  8,  3,  0,  5,
         14, 14, 14, 14, 14, 14, 14, 14, 14, 14,  0, 10,  0,  9,  0,  0,
          0, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,
         13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,  0,  0,  0,  0,  0,
          0, 15, 13, 15, 15, 13, 15, 13, 13, 15, 13, 13, 13, 15, 15, 15,
         15, 13, 15, 15, 15, 13, 15, 13, 13, 13, 13, 11,  0, 12,  0,  0,
          0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
          0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
          0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
          0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
          0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
          0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
          0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
          0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
      }; // startTab
    public Sets.Set256 ignoredChars = new Sets.Set256(
         0x0600, 0x0000, 0x0001
      ); // ignoredChars
    public Sets.Set256 commentStart = new Sets.Set256(
         0x0000
      ); // commentStart
    public Sets.Set256[] cls = {
        new Sets.Set256( 0x0000, 0x0000, 0x0000, 0x0000, 0xfffe, 0x07ff, 0xfffe, 0x07ff),
        new Sets.Set256( 0x0000, 0x0000, 0x0000, 0x03ff),
        new Sets.Set256( 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xe25a, 0x005d),
        new Sets.Set256( 0x0000, 0x0000, 0x0000, 0x0000, 0xfffe, 0x07ff, 0x1da4, 0x07a2)
      }; // cls
  } // LexicalTable

  private static LexicalTable lt;
  private static Hashtable    kwHt;  // hash table for keywords: string -> token 
  private static Hashtable    nHt;   // hash table for names: string -> spix 
  private static ArrayList    nl;    // name list  for names, spix (as index) -> string

  private static String curLineStr;  // current source line
  private static char[] tokenStrArr; // token string in an array
  private static int    tokenStrLen; // length of token string in tokenStrArr
  private static int    state;       // current automaton state
  private static int    apxLen;      // length of appendix in token string
  private static int    pendingEOLs; // nr of EOLs found in comment

  // --- to save and restore scanner state ---
  private static char   savedCh;
  private static int    savedCol, savedLine;

  private static void SaveScannerState() {
    savedCh      = curCh;
    savedCol     = curCol;
    savedLine    = curLine;
  } // SaveScannerState

  private static void RestoreScannerState() {
    tokenStrLen -= apxLen;
    apxLen       = 0;
    curCh        = savedCh;
    curCol       = savedCol;
    curLine      = savedLine;
  } // RestoreScannerState


  public static void NextCh() {
  //-----------------------------------|----------------------------------------
    while (true) {
      
      if (curCol < curLineStr.Length) {         // within line
        curCol++;
        curCh = curLineStr[curCol - 1];
        return;
      } else if (curCol == curLineStr.Length) { // end of line
        curCol++;
        curCh = Utils.LF; // to separate lines
        return;
      } else { // curCol > curLineStr.Length
        curLineStr = src.ReadLine();
        curLine++;
        curCol = 0;
        if (curLineStr == null) {               // end of file
          curLineStr = "";
          curCh = Utils.EF;
          return;
        } // if
      } // else
    } // while
  } // NextCh


  private static void CommentErr() {
    Errors.LexError(curLine, curCol, "end of file in comment");
  } // CommentErr

  private static bool Comment() {
    
    return false;
  } // Comment

  private static void HandleLexErr() {
    Errors.LexError(curLine, curCol, 
                    "invalid character '{0}' (hex {1:X})", curCh, (int)curCh);
    if (apxLen > 0)
      RestoreScannerState();
  } // HandleLexErr


  public static void GetToken() {
  //-----------------------------------|----------------------------------------
    token = -1;
    tokenStr = null;
    do {
      // --- skip ignored chars ---
      while (Sets.member(curCh, lt.ignoredChars))
        NextCh();
      // --- scan for next token ---
      tokenLine   = curLine;
      tokenCol    = curCol;
      tokenStrLen = 0;
      apxLen      = 0;
      state = (curCh == Utils.EF) ? 1 : lt.startTab[curCh];
      while (true) {
        tokenStrArr[tokenStrLen++]= curCh;
        NextCh();
        switch (state) {
          case 0:
            Errors.LexError(tokenLine, tokenCol, "invalid token start");
            break;
          case 1:
            token = 0;
            tokenStrLen = 0;
            break;                      // EOF recognized
          case 2:
            token = 6;
            break;                      // '+' recognized
          case 3:
            token = 7;
            break;                      // '-' recognized
          case 4:
            token = 8;
            break;                      // '*' recognized
          case 5:
            token = 9;
            break;                      // '/' recognized
          case 6:
            token = 10;
            break;                      // '(' recognized
          case 7:
            token = 11;
            break;                      // ')' recognized
          case 8:
            token = 12;
            break;                      // ',' recognized
          case 9:
            token = 13;
            break;                      // '=' recognized
          case 10:
            token = 14;
            break;                      // ';' recognized
          case 11:
            token = 15;
            break;                      // '{' recognized
          case 12:
            token = 16;
            break;                      // '}' recognized
          case 13:
            if (Sets.member(curCh, lt.cls[0])) {
              state = 13;
              continue;
            } // if
            else if (Sets.member(curCh, lt.cls[1])) {
              state = 13;
              continue;
            } // if
            else {
              token = KeywordCheck();
              if (token >= 0)
                break;                  // keyword recognized
              token = 17;
              break;                    // ident recognized
            } // else
          case 14:
            if (Sets.member(curCh, lt.cls[1])) {
              state = 14;
              continue;
            } // if
            else {
              token = 18;
              break;                    // number recognized
            } // else
          case 15:
            if (Sets.member(curCh, lt.cls[1])) {
              state = 13;
              continue;
            } // if
            else if (Sets.member(curCh, lt.cls[2])) {
              state = 15;
              continue;
            } // if
            else if (Sets.member(curCh, lt.cls[3])) {
              state = 13;
              continue;
            } // if
            else {
              token = KeywordCheck();
              if (token >= 0)
                break;                  // keyword recognized
              token = 17;
              break;                    // ident recognized
            } // else
        } // switch
        break;
      } // while
    } while (token < 0);
    if (tokenStr == null)
      tokenStr = new String(tokenStrArr, 0, tokenStrLen);
  } // GetToken

  private static int KeywordCheck() {
    tokenStr = new String(tokenStrArr, 0, tokenStrLen - apxLen);
    Object token = kwHt[tokenStr];
    return (token == null) ? -1 : (int)token;
  } // KeywordCheck


  public static int Hash(String s) {
  //-----------------------------------|----------------------------------------
    Object spix = nHt[s];
    if (spix == null) {
      if (caseSensitive)
        nl.Add(s);
      else
        nl.Add(s.ToUpper());
      spix   = nl.Count - 1;
      nHt[s] = spix;
    } // if
    return (int)spix;
  } // Hash
  
  
  public static String HashedStr(int spix) {
  //-----------------------------------|----------------------------------------
    return (String)nl[spix];
  } // HashedStr


  public static void GETidentAttr(out String identStr) {
    identStr = tokenStr;

  } // GETidentAttr
  
  public static void GETnumberAttr(out int numberVal) {
    numberVal = Convert.ToInt32(tokenStr);

  } // GETnumberAttr

} // MiniCLex

// End of MiniCLex.cs
//=====================================|========================================