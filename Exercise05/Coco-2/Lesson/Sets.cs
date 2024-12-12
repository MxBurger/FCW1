// Sets.cs                                      HDO, 2006-08-28 until 2023-03-13
// -------
// Definition of types AbstractSet (abstract), Set256 and Set512
// as well as methods for their manipulation.
//=====================================|========================================

#undef TEST_SETS

using System;
using System.Text;


public class Sets {

  public const String MODULENAME = "Sets";
  public const ushort USHORT_BITS = 16; // number of bits in ushort
  public const ushort MASK = 15;        // = 1111 binary


  public static void SetsMethod(Utils.ModuleAction action, out String moduleName) {
    //-----------------------------------|----------------------------------------
    moduleName = MODULENAME;
    switch (action) {
      case Utils.ModuleAction.getModuleName:
        return;
      case Utils.ModuleAction.initModule:
        break;
      case Utils.ModuleAction.resetModule:
        break;
      case Utils.ModuleAction.cleanupModule:
        break;
    } // switch
  } // SetsMethod


  // --- classes AbstractSet, Set256 and Set512  ---

  public abstract class AbstractSet {

    public readonly ushort maxElems;  // element range: 0 .. maxElems - 1
    public ushort[] ushorts;          // provides 1 bit per element

    public AbstractSet(ushort maxElems) {
      this.maxElems = maxElems;
      this.ushorts = new ushort[(ushort)(maxElems / USHORT_BITS)];
    } // AbstractSet

    public AbstractSet(ushort maxElems, params ushort[] paramUshorts)
      : this(maxElems) {
      for (int i = 0; i < paramUshorts.Length; i++)
        this.ushorts[i] = paramUshorts[i];
    } // AbstractSet

    public ushort this[int i] {
      get {
        return ushorts[i];
      } // get
      set {
        ushorts[i] = value;
      } // set
    } // this[]

    public override String ToString() {
      StringBuilder sb = new StringBuilder("{");
      bool first = true;
      for (ushort i = 0; i < maxElems; i++)
        if (member(i, this )) {
          if (!first)
            sb.Append(", ");
          sb.Append(i.ToString());
          first = false;
        } // if
      sb.Append("}");
      return sb.ToString();
    } // ToString

  } // AbstractSet


  public class Set256: AbstractSet {
    public Set256()
      : base(256) {
    } // Set256
    public Set256(params ushort[] paramUshorts)
      : base(256, paramUshorts) {
    } // Set256
  } // Set256

  public class Set512: AbstractSet {
    public Set512(): base(512) {
    } // Set512
    public Set512(params ushort[] paramUshorts)
      : base(512, paramUshorts) {
    } // Set512
  } // Set512



  public static Set256 emptySet    = new Set256(); // empty set constant
  public static Set256 emptySet256 = new Set256(); // empty set constant
  public static Set512 emptySet512 = new Set512(); // empty set constant 


  // --- element operations for and Set256 and Set512  ---

  // x member of s?
  public static bool member<Set>(ushort x, Set s) where Set: AbstractSet {
    //-----------------------------------|----------------------------------------
    if (x >= s.maxElems)
      Errors.Restriction(MODULENAME, "member", "value {0} out of set range", x);
    return (s.ushorts[x / USHORT_BITS] & (ushort)(1 << (x & MASK))) != 0;
  } // member

  // include x in s 
  public static void setincl<Set>(ref Set s, ushort x) where Set : AbstractSet {
    //-----------------------------------|----------------------------------------
    if (x >= s.maxElems)
      Errors.Restriction(MODULENAME, "setincl", "value {0} out of set range", x);
    s.ushorts[x / USHORT_BITS] |= (ushort)(1 << (x & MASK));
  } // setincl

  // exclude x from s 
  //-----------------------------------|----------------------------------------
  public static void setexcl<Set>(ref Set s, ushort x) where Set : AbstractSet {
    if (x >= s.maxElems)
      Errors.Restriction(MODULENAME, "setexcl", "value {0} out of set range", x);
    s.ushorts[x / USHORT_BITS] &= (ushort)~(1 << (x & MASK));
  } // setexcl


   // init s, use
   //   e or E for an <e>lement, e.g., setinit(s, "E", e)
   //   r or R for a  <r>ange,   e.g., setinit(s, "R", lb, ub) 
  public static void setinit<Set>(out Set s, String form, params ushort[] p) 
    where Set: AbstractSet, new() {
    //-----------------------------------|----------------------------------------
    ushort e, lb, ub;
    int i = 0;
    s = new Set();
    foreach (char op in form) {
      switch (Char.ToUpper(op)) {
        case 'E':
          e = p[i++];  // single element e
          setincl(ref s, e);
          break;
        case 'R':
          lb = p[i++]; // range lb .. ub
          ub = p[i++];
          if (lb > ub)
            Utils.FatalError(MODULENAME, "setinit", "range error: lb > ub");
          for (e = lb; e <= ub; e++) 
            setincl(ref s, e);
          break;
        default:
          Utils.FatalError(MODULENAME, "setinit", "invalid operation {0}", op);
          break;
      } // switch
    } // while
  } // setinit


  // --- set operations for types Set256 and Set512  ---

  // s1 <= s2? 
  public static bool setle<Set>(Set s1, Set s2) where Set : AbstractSet {
    //-----------------------------------|----------------------------------------
    for (int i = 0; i < s1.ushorts.Length; i++)
      if ((s1.ushorts[i] & ~(s2.ushorts[i])) != 0)
        return false;
      return true;
    } // setle

    // sets s1 and s2 disjoint?
    public static bool setdisjoint<Set>(Set s1, Set s2) where Set : AbstractSet {
    //-----------------------------------|----------------------------------------
    for (int i = 0; i < s1.ushorts.Length; i++)
      if ((s1.ushorts[i] & s2.ushorts[i]) != 0)
        return false;
    return true;
  } // setdisjoint

  // s1 = s1 inters s2 
  public static void setinters<Set>(ref Set s1, Set s2) where Set : AbstractSet {
    //-----------------------------------|----------------------------------------
    for (int i = 0; i < s1.ushorts.Length; i++)
      s1.ushorts[i] &= s2.ushorts[i];
  } // setinters

  // s1 = s1 union s2
  public static void setunion<Set>(ref Set s1, Set s2) where Set : AbstractSet {
    //-----------------------------------|----------------------------------------
    for (int i = 0; i < s1.ushorts.Length; i++)
      s1.ushorts[i] |= s2.ushorts[i];
  } // setunion

  // s1 = s1 - s2 
  public static void setdiff<Set> (ref Set s1, Set s2) where Set : AbstractSet {
    //-----------------------------------|----------------------------------------
    for (int i = 0; i < s1.ushorts.Length; i++)
      s1.ushorts[i] &= (ushort)~s2.ushorts[i];
  } // setdiff

  // clear s, s = {}
  public static void setclear<Set>(ref Set s) where Set : AbstractSet {
    //-----------------------------------|----------------------------------------
    for (int i = 0; i < s.ushorts.Length; i++)
      s.ushorts[i] = 0;
  } // setclear

  // set assignment, s1 = s2
  public static void setcpy<Set>(ref Set s1, Set s2) where Set : AbstractSet {
    //-----------------------------------|----------------------------------------
    for (int i = 0; i < s1.ushorts.Length; i++)
      s1.ushorts[i] = s2.ushorts[i];
  } // setcpy

  // set comparison, s1 == s2? 
  public static bool seteq<Set>(Set s1, Set s2) where Set : AbstractSet {
    //-----------------------------------|----------------------------------------
    for (int i = 0; i < s1.ushorts.Length; i++)
      if (s1.ushorts[i] != s2.ushorts[i])
        return false;
    return true;
  } // seteq

  // s empty?, s = {}?
  public static bool setempty<Set> (Set s) where Set : AbstractSet {
    //-----------------------------------|----------------------------------------
    for (int i = 0; i < s.ushorts.Length; i++)
      if (s.ushorts[i] != 0)
        return false;
    return true;
  } // setempty


#if TEST_SETS

  public static void Main(String[] args) {
    Console.WriteLine("START: Sets");

    Console.WriteLine("installing ...");
    Utils.InstallModule("Utils", new Utils.ModuleMethodDelegate(Utils.UtilsMethod));
    Utils.InstallModule("Sets",  new Utils.ModuleMethodDelegate(Sets.SetsMethod ));
    Console.WriteLine("initModule ...");
    Utils.Modules(Utils.ModuleAction.initModule);

    Console.WriteLine("emptySet256 = " + emptySet256);
    Console.WriteLine("emptySet512 = " + emptySet512);

    Set512 s = new Set512();
    Console.WriteLine("s = " + s);
    setincl(ref s, 177);
    setincl(ref s, 4);
    Console.WriteLine("after setincl(ref s, 177) and setincl(ref s, 4), s = " + s);
    setexcl(ref s, 177);
    setexcl(ref s, 4);
    Console.WriteLine("after setexcl(ref s, 177) and setexcl(ref s, 4), s = " + s);

    setinit(out s, "E", 4);
    Console.WriteLine("after setinit(out s, \"E\", 4), s = " + s);
    setinit(out s, "R", 250, 300);
    Console.WriteLine("after setinit(out s, \"R\", 250, 300), s = " + s);

    Set256 a = new Set256();
    Set256 b = new Set256();
    setinit(out a, "R",   0,   9);
    setinit(out b, "R",   9,  100);
    Console.WriteLine("setdisjoint(a, b) = " + setdisjoint(a, b));

    setinit(out a, "R", 0, 99);
    setinit(out b, "R", 80, 100);
    setinters(ref a, b);
    Console.WriteLine("setinters(ref a, b) = " + a);

    setinit(out a, "R", 0, 9);
    setinit(out b, "R", 100, 109);
    setunion(ref a, b);
    Console.WriteLine("setunion(ref a, b) = " + a);

    setinit(out a, "R", 0, 99);
    setinit(out b, "R", 1, 98);
    setdiff(ref a, b);
    Console.WriteLine("setdiff(ref a, b) = " + a);

    setclear(ref a);
    Console.WriteLine("setclear(a) = " + a);

    setinit(out b, "R", 0, 9);
    setcpy(ref a, b);
    Console.WriteLine("setcpy(a) = " + a);

    Console.WriteLine("seteq(a, b) = " + seteq(a, b));

    Console.WriteLine("setempty(a) = " + setempty(a));
    Console.WriteLine("setempty(emptySet256) = " + setempty(emptySet256));

    Console.WriteLine("resetModule ...");
    Utils.Modules(Utils.ModuleAction.resetModule);

    Console.WriteLine("cleanupModule ...");
    Utils.Modules(Utils.ModuleAction.cleanupModule);
    Console.WriteLine("END");
    // Console.WriteLine("type [CR] to continue ...");
    // Console.ReadLine();
  } // Main

#endif

} // Sets

// End of Sets.cs
//=====================================|========================================
