/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y23
 */
import java.util.*;
import org.mozilla.javascript.*;
import xdc.services.intern.xsr.*;
import xdc.services.spec.Session;

public class ti_uia_examples
{
    static final String VERS = "@(#) xdc-y23\n";

    static final Proto.Elm $$T_Bool = Proto.Elm.newBool();
    static final Proto.Elm $$T_Num = Proto.Elm.newNum();
    static final Proto.Elm $$T_Str = Proto.Elm.newStr();
    static final Proto.Elm $$T_Obj = Proto.Elm.newObj();

    static final Proto.Fxn $$T_Met = new Proto.Fxn(null, null, 0, -1, false);
    static final Proto.Map $$T_Map = new Proto.Map($$T_Obj);
    static final Proto.Arr $$T_Vec = new Proto.Arr($$T_Obj);

    static final XScriptO $$DEFAULT = Value.DEFAULT;
    static final Object $$UNDEF = Undefined.instance;

    static final Proto.Obj $$Package = (Proto.Obj)Global.get("$$Package");
    static final Proto.Obj $$Module = (Proto.Obj)Global.get("$$Module");
    static final Proto.Obj $$Instance = (Proto.Obj)Global.get("$$Instance");
    static final Proto.Obj $$Params = (Proto.Obj)Global.get("$$Params");

    static final Object $$objFldGet = Global.get("$$objFldGet");
    static final Object $$objFldSet = Global.get("$$objFldSet");
    static final Object $$proxyGet = Global.get("$$proxyGet");
    static final Object $$proxySet = Global.get("$$proxySet");
    static final Object $$delegGet = Global.get("$$delegGet");
    static final Object $$delegSet = Global.get("$$delegSet");

    Scriptable xdcO;
    Session ses;
    Value.Obj om;

    boolean isROV;
    boolean isCFG;

    Proto.Obj pkgP;
    Value.Obj pkgV;

    ArrayList<Object> imports = new ArrayList<Object>();
    ArrayList<Object> loggables = new ArrayList<Object>();
    ArrayList<Object> mcfgs = new ArrayList<Object>();
    ArrayList<Object> icfgs = new ArrayList<Object>();
    ArrayList<String> inherits = new ArrayList<String>();
    ArrayList<Object> proxies = new ArrayList<Object>();
    ArrayList<Object> sizes = new ArrayList<Object>();
    ArrayList<Object> tdefs = new ArrayList<Object>();

    void $$IMPORTS()
    {
        Global.callFxn("loadPackage", xdcO, "xdc");
        Global.callFxn("loadPackage", xdcO, "xdc.corevers");
        Global.callFxn("loadPackage", xdcO, "xdc.tools.product");
    }

    void $$OBJECTS()
    {
        pkgP = (Proto.Obj)om.bind("ti.uia.examples.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.uia.examples", new Value.Obj("ti.uia.examples", pkgP));
    }

    void Examples$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.uia.examples.Examples.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.uia.examples.Examples", new Value.Obj("ti.uia.examples.Examples", po));
        pkgV.bind("Examples", vo);
        // decls 
        om.bind("ti.uia.examples.Examples.FileDesc", om.findStrict("xdc.tools.product.IProductTemplate.FileDesc", "ti.uia.examples"));
        om.bind("ti.uia.examples.Examples.Filter", om.findStrict("xdc.tools.product.IProductTemplate.Filter", "ti.uia.examples"));
        om.bind("ti.uia.examples.Examples.TemplateInfo", om.findStrict("xdc.tools.product.IProductTemplate.TemplateInfo", "ti.uia.examples"));
        om.bind("ti.uia.examples.Examples.TemplateGroup", om.findStrict("xdc.tools.product.IProductTemplate.TemplateGroup", "ti.uia.examples"));
    }

    void Examples$$CONSTS()
    {
        // module Examples
    }

    void Examples$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void Examples$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void Examples$$SIZES()
    {
    }

    void Examples$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        po = (Proto.Obj)om.findStrict("ti.uia.examples.Examples.Module", "ti.uia.examples");
        po.init("ti.uia.examples.Examples.Module", om.findStrict("xdc.tools.product.IProductTemplate.Module", "ti.uia.examples"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
        po.addFld("name", $$T_Str, "System Analyzer (UIA) Examples", "wh");
        po.addFld("root", (Proto)om.findStrict("xdc.tools.product.IProductTemplate.TemplateGroup", "ti.uia.examples"), Global.newObject("id", "ti.uia.examples.root", "name", "System Analyzer (UIA)", "description", "System Analyzer (UIA) Tutorials, Examples and Project Templates"), "wh");
        po.addFld("level1", (Proto)om.findStrict("xdc.tools.product.IProductTemplate.TemplateGroup", "ti.uia.examples"), Global.newObject("id", "ti.uia.examples.root.level1", "name", "Single-core Examples", "description", "System Analyzer (UIA) Single-core Examples", "groups", Global.newArray(new Object[]{"ti.uia.examples.root"})), "wh");
        po.addFld("level2", (Proto)om.findStrict("xdc.tools.product.IProductTemplate.TemplateGroup", "ti.uia.examples"), Global.newObject("id", "ti.uia.examples.root.level2", "name", "Multi-core Projects", "description", "System Analyzer (UIA) Multi-core Examples", "groups", Global.newArray(new Object[]{"ti.uia.examples.root"})), "wh");
        po.addFld("level3", (Proto)om.findStrict("xdc.tools.product.IProductTemplate.TemplateGroup", "ti.uia.examples"), Global.newObject("id", "ti.uia.examples.root.level3", "name", "Tutorials", "description", "System Analyzer (UIA) Tutorials", "groups", Global.newArray(new Object[]{"ti.uia.examples.root"})), "wh");
        po.addFld("templateGroupArr", new Proto.Arr((Proto)om.findStrict("xdc.tools.product.IProductTemplate.TemplateGroup", "ti.uia.examples"), false), Global.newArray(new Object[]{Global.newObject("id", "ti.uia.examples.root", "name", "System Analyzer (UIA)", "description", "System Analyzer (UIA) Tutorials, Examples and Project Templates"), Global.newObject("id", "ti.uia.examples.root.level1", "name", "Single-core Examples", "description", "System Analyzer (UIA) Single-core Examples", "groups", Global.newArray(new Object[]{"ti.uia.examples.root"})), Global.newObject("id", "ti.uia.examples.root.level2", "name", "Multi-core Projects", "description", "System Analyzer (UIA) Multi-core Examples", "groups", Global.newArray(new Object[]{"ti.uia.examples.root"})), Global.newObject("id", "ti.uia.examples.root.level3", "name", "Tutorials", "description", "System Analyzer (UIA) Tutorials", "groups", Global.newArray(new Object[]{"ti.uia.examples.root"}))}), "wh");
        po.addFld("c6472_message", (Proto)om.findStrict("xdc.tools.product.IProductTemplate.TemplateInfo", "ti.uia.examples"), Global.newObject("title", "evm6472: MessageQ (single image for all cores) with UIA", "fileList", Global.newArray(new Object[]{Global.newObject("path", "./evm6472/message.c"), Global.newObject("path", "./evm6472/message.cfg")}), "description", "The message example shows how to use MessageQ on EVM6472 and UIA. It is a single-image example that must be loaded on all cores.\\n\\nA message is sent from core 0 to core 1 to core 2...back to core 0. The UIABenchmark_start and stop is used on core 0 to determine the duration of a round trip.\\n\\nThe Log data is obtained via Ethernet.", "buildProfile", "release", "platform", "ti.platforms.evm6472:core0", "groups", Global.newArray(new Object[]{"ti.uia.examples.root.level2"}), "isHybrid", true, "filterArr", Global.newArray(new Object[]{Global.newObject("deviceFamily", "C6000", "toolChain", "TI")}), "requiredProducts", Global.newArray(new Object[]{"com.ti.rtsc.SYSBIOS", "com.ti.rtsc.IPC", "com.ti.rtsc.NDK"}), "linkerCommandFile", ""), "wh");
        po.addFld("stairstep_JTAGStopMode", (Proto)om.findStrict("xdc.tools.product.IProductTemplate.TemplateInfo", "ti.uia.examples"), Global.newObject("title", "Stairstep JTAG StopMode", "fileList", Global.newArray(new Object[]{Global.newObject("path", "./single/stairstep.c"), Global.newObject("path", "./single/stairstep_JTAGStopMode.cfg")}), "description", "The stairstep example runs continusously and periodically generates log events. Different threads (Hwi, Swi, Task) run to present a CPU load to the system.\\n\\nThe Log data is obtained when the target is halted.\\n\\nThe sizes of the loggers in LoggingSetup might need to be decreased if your target does not have enough memory.", "buildProfile", "release", "groups", Global.newArray(new Object[]{"ti.uia.examples.root.level1"}), "isHybrid", true, "filterArr", Global.newArray(new Object[]{Global.newObject("deviceFamily", "C6000", "toolChain", "TI"), Global.newObject("deviceFamily", "ARM", "toolChain", "TI"), Global.newObject("deviceFamily", "C2000", "toolChain", "TI")}), "requiredProducts", Global.newArray(new Object[]{"com.ti.rtsc.SYSBIOS", "com.ti.rtsc.IPC"}), "linkerCommandFile", ""), "wh");
        po.addFld("logger", (Proto)om.findStrict("xdc.tools.product.IProductTemplate.TemplateInfo", "ti.uia.examples"), Global.newObject("title", "LoggerStreamer Example", "fileList", Global.newArray(new Object[]{Global.newObject("path", "./single/logger.c"), Global.newObject("path", "./single/logger.cfg")}), "description", "Example showing the usage of LoggerStreamer and LogUC.h", "buildProfile", "release", "groups", Global.newArray(new Object[]{"ti.uia.examples.root.level1"}), "isHybrid", true, "filterArr", Global.newArray(new Object[]{Global.newObject("deviceFamily", "C6000", "toolChain", "TI"), Global.newObject("deviceFamily", "ARM", "toolChain", "TI"), Global.newObject("deviceFamily", "C2000", "toolChain", "TI")}), "requiredProducts", Global.newArray(new Object[]{"com.ti.rtsc.SYSBIOS", "com.ti.rtsc.IPC"}), "linkerCommandFile", ""), "wh");
        po.addFld("stairstep_ProbePoint", (Proto)om.findStrict("xdc.tools.product.IProductTemplate.TemplateInfo", "ti.uia.examples"), Global.newObject("title", "Stairstep ProbePoint", "fileList", Global.newArray(new Object[]{Global.newObject("path", "./single/stairstep.c"), Global.newObject("path", "./single/stairstep_ProbePoint.cfg")}), "description", "The stairstep example runs continusously and periodically generates log events. Different threads (Hwi, Swi, Task) run to present a CPU load to the system.\\n\\nThe Log data is obtained by temporarily stopping the target when the Log call is made.\\n\\nThe sizes of the loggers in LoggingSetup might need to be decreased if your target does not have enough memory.\\n\\nTo build this example, the XDC version must be 3.22 (or later) or the RTSC Build-Profile must be \"release\" or \"debug\" (not \"whole_program\").", "buildProfile", "release", "groups", Global.newArray(new Object[]{"ti.uia.examples.root.level1"}), "isHybrid", true, "filterArr", Global.newArray(new Object[]{Global.newObject("deviceFamily", "C6000", "toolChain", "TI"), Global.newObject("deviceFamily", "ARM", "toolChain", "TI"), Global.newObject("deviceFamily", "C2000", "toolChain", "TI")}), "requiredProducts", Global.newArray(new Object[]{"com.ti.rtsc.SYSBIOS", "com.ti.rtsc.IPC"}), "linkerCommandFile", ""), "wh");
        po.addFld("stairstep_JTAGRunMode", (Proto)om.findStrict("xdc.tools.product.IProductTemplate.TemplateInfo", "ti.uia.examples"), Global.newObject("title", "Stairstep JTAG RunMode", "fileList", Global.newArray(new Object[]{Global.newObject("path", "./single/stairstep.c"), Global.newObject("path", "./single/stairstep_JTAGRunMode.cfg")}), "description", "The stairstep example runs continusously and periodically generates log events. Different threads (Hwi, Swi, Task) run to present a CPU load to the system.\\n\\nThe Log data is obtained by reading the running target (only works on C64X+ and C66 CPUs).\\n\\nThe sizes of the loggers in LoggingSetup might need to be decreased if your target does not have enough memory.", "buildProfile", "release", "groups", Global.newArray(new Object[]{"ti.uia.examples.root.level1"}), "isHybrid", true, "filterArr", Global.newArray(new Object[]{Global.newObject("deviceFamily", "C6000", "toolChain", "TI")}), "requiredProducts", Global.newArray(new Object[]{"com.ti.rtsc.SYSBIOS", "com.ti.rtsc.IPC"}), "linkerCommandFile", ""), "wh");
        po.addFld("stairstep_Ethernet", (Proto)om.findStrict("xdc.tools.product.IProductTemplate.TemplateInfo", "ti.uia.examples"), Global.newObject("title", "Stairstep Ethernet", "fileList", Global.newArray(new Object[]{Global.newObject("path", "./single/stairstep.c"), Global.newObject("path", "./single/stairstep_Ethernet.cfg")}), "description", "The stairstep example runs continuously and periodically generates log events. Different threads (Hwi, Swi, Task) run to present a CPU load to the system.\\n\\nLog data is obtained via Ethernet.\\n\\nThe sizes of the loggers in LoggingSetup might need to be decreased if your target does not have enough memory.\\n\\nThis example, as is, only works for the EVM6472 board. Refer to the bottom of the .cfg file on how to use on a different board.", "buildProfile", "release", "groups", Global.newArray(new Object[]{"ti.uia.examples.root.level1"}), "isHybrid", true, "filterArr", Global.newArray(new Object[]{Global.newObject("deviceFamily", "C6000", "toolChain", "TI"), Global.newObject("deviceFamily", "ARM", "toolChain", "TI")}), "requiredProducts", Global.newArray(new Object[]{"com.ti.rtsc.SYSBIOS", "com.ti.rtsc.IPC", "com.ti.rtsc.NDK"}), "linkerCommandFile", ""), "wh");
        po.addFld("stairstep_Simulator", (Proto)om.findStrict("xdc.tools.product.IProductTemplate.TemplateInfo", "ti.uia.examples"), Global.newObject("title", "Stairstep Simulator", "fileList", Global.newArray(new Object[]{Global.newObject("path", "./single/stairstep.c"), Global.newObject("path", "./single/stairstep_Simulator.cfg")}), "description", "The stairstep example runs continusously and periodically generates log events. Different threads (Hwi, Swi, Task) run to present a CPU load to the system.\\n\\nThe Log data is obtained by temporarily stopping the target when the Log call is made.\\n\\nThe sizes of the loggers in LoggingSetup might need to be decreased if your target does not have enough memory\\n\\nTo build this example, the XDC version must be 3.22 (or later) or the RTSC Build-Profile must be \"release\" or \"debug\" (not \"whole_program\").", "buildProfile", "release", "groups", Global.newArray(new Object[]{"ti.uia.examples.root.level1"}), "isHybrid", true, "filterArr", Global.newArray(new Object[]{Global.newObject("deviceFamily", "C6000", "toolChain", "TI"), Global.newObject("deviceFamily", "ARM", "toolChain", "TI"), Global.newObject("deviceFamily", "C2000", "toolChain", "TI")}), "requiredProducts", Global.newArray(new Object[]{"com.ti.rtsc.SYSBIOS", "com.ti.rtsc.IPC"}), "linkerCommandFile", ""), "wh");
        po.addFld("evmti816x_dspLoggerCircBuf", (Proto)om.findStrict("xdc.tools.product.IProductTemplate.TemplateInfo", "ti.uia.examples"), Global.newObject("title", "evmti816x: SimpleTask w/ LoggerCircBuf for the DSP", "fileList", Global.newArray(new Object[]{Global.newObject("path", "./evmti816x/simpleTask.c"), Global.newObject("path", "./evmti816x/dspLoggerCircBuf.cfg")}), "description", "This DSP example uses LoggerCircBuf to log benchmark events. The events are routed through the ServiceMgr on Linux.\\n\\nThe program benchmarks the duration to run an \"algorithm\"\\n\\nRefer to the Getting Started Guide for a more detailed description.", "groups", Global.newArray(new Object[]{"ti.uia.examples.root.level2"}), "buildProfile", "release", "platform", "ti.uia.examples.platforms.evmTI816X.dsp", "isHybrid", true, "filterArr", Global.newArray(new Object[]{Global.newObject("deviceFamily", "C6000", "toolChain", "TI")}), "requiredProducts", Global.newArray(new Object[]{"com.ti.rtsc.SYSBIOS", "com.ti.rtsc.IPC"}), "linkerCommandFile", ""), "wh");
        po.addFld("evmti816x_videoM3LoggerCircBuf", (Proto)om.findStrict("xdc.tools.product.IProductTemplate.TemplateInfo", "ti.uia.examples"), Global.newObject("title", "evmti816x: SimpleTask w/ LoggerCircBuf for the video M3", "fileList", Global.newArray(new Object[]{Global.newObject("path", "./evmti816x/simpleTask.c"), Global.newObject("path", "./evmti816x/videoM3LoggerCircBuf.cfg")}), "description", "This Video M3 example uses LoggerCircBuf to log benchmark events. The events are routed through the ServiceMgr on Linux.\\n\\nThe program benchmarks the duration to run an \"algorithm\"\\n\\nRefer to the Getting Started Guide for a more detailed description.", "groups", Global.newArray(new Object[]{"ti.uia.examples.root.level2"}), "buildProfile", "release", "platform", "ti.uia.examples.platforms.evmTI816X.video", "isHybrid", true, "filterArr", Global.newArray(new Object[]{Global.newObject("deviceFamily", "ARM", "toolChain", "TI")}), "requiredProducts", Global.newArray(new Object[]{"com.ti.rtsc.SYSBIOS", "com.ti.rtsc.IPC"}), "linkerCommandFile", ""), "wh");
        po.addFld("evmti816x_vpssM3LoggerCircBuf", (Proto)om.findStrict("xdc.tools.product.IProductTemplate.TemplateInfo", "ti.uia.examples"), Global.newObject("title", "evmti816x: SimpleTask w/ LoggerCircBuf for the vpss M3", "fileList", Global.newArray(new Object[]{Global.newObject("path", "./evmti816x/simpleTask.c"), Global.newObject("path", "./evmti816x/vpssM3LoggerCircBuf.cfg")}), "description", "This VPSS M3 example uses LoggerCircBuf to log benchmark events. The events are routed through the ServiceMgr on Linux.\\n\\nThe program benchmarks the duration to run an \"algorithm\"\\n\\nRefer to the Getting Started Guide for a more detailed description.", "groups", Global.newArray(new Object[]{"ti.uia.examples.root.level2"}), "buildProfile", "release", "platform", "ti.uia.examples.platforms.evmTI816X.vpss", "isHybrid", true, "filterArr", Global.newArray(new Object[]{Global.newObject("deviceFamily", "ARM", "toolChain", "TI")}), "requiredProducts", Global.newArray(new Object[]{"com.ti.rtsc.SYSBIOS", "com.ti.rtsc.IPC"}), "linkerCommandFile", ""), "wh");
        po.addFld("evmti816x_dspLoggerSM", (Proto)om.findStrict("xdc.tools.product.IProductTemplate.TemplateInfo", "ti.uia.examples"), Global.newObject("title", "evmti816x: SimpleTask w/ LoggerSM for the DSP", "fileList", Global.newArray(new Object[]{Global.newObject("path", "./evmti816x/simpleTask.c"), Global.newObject("path", "./evmti816x/dspLoggerSM.cfg")}), "description", "This DSP example uses LoggerSM to log benchmark events. The events can be displayed to the Linux console or written to a binary file.\\n\\nThe program benchmarks the duration to run an \"algorithm\"\\n\\nRefer to the Getting Started Guide for a more detailed description.", "groups", Global.newArray(new Object[]{"ti.uia.examples.root.level2"}), "buildProfile", "release", "platform", "ti.uia.examples.platforms.evmTI816X.dsp", "isHybrid", true, "filterArr", Global.newArray(new Object[]{Global.newObject("deviceFamily", "C6000", "toolChain", "TI")}), "requiredProducts", Global.newArray(new Object[]{"com.ti.rtsc.SYSBIOS", "com.ti.rtsc.IPC"}), "linkerCommandFile", ""), "wh");
        po.addFld("evmti816x_videoM3LoggerSM", (Proto)om.findStrict("xdc.tools.product.IProductTemplate.TemplateInfo", "ti.uia.examples"), Global.newObject("title", "evmti816x: SimpleTask w/ LoggerSM for the video M3", "fileList", Global.newArray(new Object[]{Global.newObject("path", "./evmti816x/simpleTask.c"), Global.newObject("path", "./evmti816x/videoM3LoggerSM.cfg")}), "description", "This Video M3 example uses LoggerSM to log benchmark events. The events can be displayed to the Linux console or written to a binary file.\\n\\nThe program benchmarks the duration to run an \"algorithm\"\\n\\nRefer to the Getting Started Guide for a more detailed description.", "groups", Global.newArray(new Object[]{"ti.uia.examples.root.level2"}), "buildProfile", "release", "platform", "ti.uia.examples.platforms.evmTI816X.video", "isHybrid", true, "filterArr", Global.newArray(new Object[]{Global.newObject("deviceFamily", "ARM", "toolChain", "TI")}), "requiredProducts", Global.newArray(new Object[]{"com.ti.rtsc.SYSBIOS", "com.ti.rtsc.IPC"}), "linkerCommandFile", ""), "wh");
        po.addFld("evmti816x_vpssM3LoggerSM", (Proto)om.findStrict("xdc.tools.product.IProductTemplate.TemplateInfo", "ti.uia.examples"), Global.newObject("title", "evmti816x: SimpleTask w/ LoggerSM for the vpss M3", "fileList", Global.newArray(new Object[]{Global.newObject("path", "./evmti816x/simpleTask.c"), Global.newObject("path", "./evmti816x/vpssM3LoggerSM.cfg")}), "description", "This VPSS M3 example uses LoggerSM to log benchmark events. The events can be displayed to the Linux console or written to a binary file.\\n\\nThe program benchmarks the duration to run an \"algorithm\"\\n\\nRefer to the Getting Started Guide for a more detailed description.", "groups", Global.newArray(new Object[]{"ti.uia.examples.root.level2"}), "buildProfile", "release", "platform", "ti.uia.examples.platforms.evmTI816X.vpss", "isHybrid", true, "filterArr", Global.newArray(new Object[]{Global.newObject("deviceFamily", "ARM", "toolChain", "TI")}), "requiredProducts", Global.newArray(new Object[]{"com.ti.rtsc.SYSBIOS", "com.ti.rtsc.IPC"}), "linkerCommandFile", ""), "wh");
        po.addFld("tutorial1", (Proto)om.findStrict("xdc.tools.product.IProductTemplate.TemplateInfo", "ti.uia.examples"), Global.newObject("title", "System Analyzer and UIA Tutorial 1: Logging events, benchmarking, controlling events.", "fileList", Global.newArray(new Object[]{Global.newObject("path", "./tutorial1/main.c"), Global.newObject("path", "./tutorial1/tutorial1a.c"), Global.newObject("path", "./tutorial1/tutorial1b.c"), Global.newObject("path", "./tutorial1/tutorial1c.c"), Global.newObject("path", "./tutorial1/tutorial1d.c"), Global.newObject("path", "./tutorial1/systemAnalyzerTutorial1.gel"), Global.newObject("path", "./tutorial1/systemAnalyzerTutorial1.cfg")}), "description", "This tutorial shows how to log errors, warnings and info events, benchmark code and control which events are logged. Refer to http://processors.wiki.ti.com/index.php/McsaTutorial1 for more details.", "groups", Global.newArray(new Object[]{"ti.uia.examples.root.level3"}), "buildProfile", "release", "isHybrid", true, "filterArr", Global.newArray(new Object[]{Global.newObject("deviceFamily", "C6000", "toolChain", "TI"), Global.newObject("deviceFamily", "ARM", "toolChain", "TI"), Global.newObject("deviceFamily", "C2000", "toolChain", "TI")}), "requiredProducts", Global.newArray(new Object[]{}), "linkerCommandFile", ""), "wh");
        po.addFld("tutorial2", (Proto)om.findStrict("xdc.tools.product.IProductTemplate.TemplateInfo", "ti.uia.examples"), Global.newObject("title", "System Analyzer and UIA Tutorial 2: Graphing events, using JTAG Run-Mode (C64X+ or C66X emulation target)", "fileList", Global.newArray(new Object[]{Global.newObject("path", "./tutorial2/main.c"), Global.newObject("path", "./tutorial2/systemAnalyzerTutorial2.gel"), Global.newObject("path", "./tutorial2/systemAnalyzerTutorial2.cfg")}), "description", "This tutorial shows how to log data that can be graphed and analyzed for min/max/average statistics.  Also demonstrates how to use LoggerCircBuf and JTAG Run-Mode to upload events while a target is running . Refer to http://processors.wiki.ti.com/index.php/McsaTutorial2 for more details.", "groups", Global.newArray(new Object[]{"ti.uia.examples.root.level3"}), "buildProfile", "release", "isHybrid", true, "filterArr", Global.newArray(new Object[]{Global.newObject("deviceFamily", "C6000", "toolChain", "TI")}), "requiredProducts", Global.newArray(new Object[]{}), "linkerCommandFile", ""), "wh");
        po.addFld("templateArr", new Proto.Arr((Proto)om.findStrict("xdc.tools.product.IProductTemplate.TemplateInfo", "ti.uia.examples"), false), Global.newArray(new Object[]{Global.newObject("title", "evm6472: MessageQ (single image for all cores) with UIA", "fileList", Global.newArray(new Object[]{Global.newObject("path", "./evm6472/message.c"), Global.newObject("path", "./evm6472/message.cfg")}), "description", "The message example shows how to use MessageQ on EVM6472 and UIA. It is a single-image example that must be loaded on all cores.\\n\\nA message is sent from core 0 to core 1 to core 2...back to core 0. The UIABenchmark_start and stop is used on core 0 to determine the duration of a round trip.\\n\\nThe Log data is obtained via Ethernet.", "buildProfile", "release", "platform", "ti.platforms.evm6472:core0", "groups", Global.newArray(new Object[]{"ti.uia.examples.root.level2"}), "isHybrid", true, "filterArr", Global.newArray(new Object[]{Global.newObject("deviceFamily", "C6000", "toolChain", "TI")}), "requiredProducts", Global.newArray(new Object[]{"com.ti.rtsc.SYSBIOS", "com.ti.rtsc.IPC", "com.ti.rtsc.NDK"}), "linkerCommandFile", ""), Global.newObject("title", "Stairstep JTAG StopMode", "fileList", Global.newArray(new Object[]{Global.newObject("path", "./single/stairstep.c"), Global.newObject("path", "./single/stairstep_JTAGStopMode.cfg")}), "description", "The stairstep example runs continusously and periodically generates log events. Different threads (Hwi, Swi, Task) run to present a CPU load to the system.\\n\\nThe Log data is obtained when the target is halted.\\n\\nThe sizes of the loggers in LoggingSetup might need to be decreased if your target does not have enough memory.", "buildProfile", "release", "groups", Global.newArray(new Object[]{"ti.uia.examples.root.level1"}), "isHybrid", true, "filterArr", Global.newArray(new Object[]{Global.newObject("deviceFamily", "C6000", "toolChain", "TI"), Global.newObject("deviceFamily", "ARM", "toolChain", "TI"), Global.newObject("deviceFamily", "C2000", "toolChain", "TI")}), "requiredProducts", Global.newArray(new Object[]{"com.ti.rtsc.SYSBIOS", "com.ti.rtsc.IPC"}), "linkerCommandFile", ""), Global.newObject("title", "Stairstep Ethernet", "fileList", Global.newArray(new Object[]{Global.newObject("path", "./single/stairstep.c"), Global.newObject("path", "./single/stairstep_Ethernet.cfg")}), "description", "The stairstep example runs continuously and periodically generates log events. Different threads (Hwi, Swi, Task) run to present a CPU load to the system.\\n\\nLog data is obtained via Ethernet.\\n\\nThe sizes of the loggers in LoggingSetup might need to be decreased if your target does not have enough memory.\\n\\nThis example, as is, only works for the EVM6472 board. Refer to the bottom of the .cfg file on how to use on a different board.", "buildProfile", "release", "groups", Global.newArray(new Object[]{"ti.uia.examples.root.level1"}), "isHybrid", true, "filterArr", Global.newArray(new Object[]{Global.newObject("deviceFamily", "C6000", "toolChain", "TI"), Global.newObject("deviceFamily", "ARM", "toolChain", "TI")}), "requiredProducts", Global.newArray(new Object[]{"com.ti.rtsc.SYSBIOS", "com.ti.rtsc.IPC", "com.ti.rtsc.NDK"}), "linkerCommandFile", ""), Global.newObject("title", "Stairstep JTAG RunMode", "fileList", Global.newArray(new Object[]{Global.newObject("path", "./single/stairstep.c"), Global.newObject("path", "./single/stairstep_JTAGRunMode.cfg")}), "description", "The stairstep example runs continusously and periodically generates log events. Different threads (Hwi, Swi, Task) run to present a CPU load to the system.\\n\\nThe Log data is obtained by reading the running target (only works on C64X+ and C66 CPUs).\\n\\nThe sizes of the loggers in LoggingSetup might need to be decreased if your target does not have enough memory.", "buildProfile", "release", "groups", Global.newArray(new Object[]{"ti.uia.examples.root.level1"}), "isHybrid", true, "filterArr", Global.newArray(new Object[]{Global.newObject("deviceFamily", "C6000", "toolChain", "TI")}), "requiredProducts", Global.newArray(new Object[]{"com.ti.rtsc.SYSBIOS", "com.ti.rtsc.IPC"}), "linkerCommandFile", ""), Global.newObject("title", "Stairstep ProbePoint", "fileList", Global.newArray(new Object[]{Global.newObject("path", "./single/stairstep.c"), Global.newObject("path", "./single/stairstep_ProbePoint.cfg")}), "description", "The stairstep example runs continusously and periodically generates log events. Different threads (Hwi, Swi, Task) run to present a CPU load to the system.\\n\\nThe Log data is obtained by temporarily stopping the target when the Log call is made.\\n\\nThe sizes of the loggers in LoggingSetup might need to be decreased if your target does not have enough memory.\\n\\nTo build this example, the XDC version must be 3.22 (or later) or the RTSC Build-Profile must be \"release\" or \"debug\" (not \"whole_program\").", "buildProfile", "release", "groups", Global.newArray(new Object[]{"ti.uia.examples.root.level1"}), "isHybrid", true, "filterArr", Global.newArray(new Object[]{Global.newObject("deviceFamily", "C6000", "toolChain", "TI"), Global.newObject("deviceFamily", "ARM", "toolChain", "TI"), Global.newObject("deviceFamily", "C2000", "toolChain", "TI")}), "requiredProducts", Global.newArray(new Object[]{"com.ti.rtsc.SYSBIOS", "com.ti.rtsc.IPC"}), "linkerCommandFile", ""), Global.newObject("title", "LoggerStreamer Example", "fileList", Global.newArray(new Object[]{Global.newObject("path", "./single/logger.c"), Global.newObject("path", "./single/logger.cfg")}), "description", "Example showing the usage of LoggerStreamer and LogUC.h", "buildProfile", "release", "groups", Global.newArray(new Object[]{"ti.uia.examples.root.level1"}), "isHybrid", true, "filterArr", Global.newArray(new Object[]{Global.newObject("deviceFamily", "C6000", "toolChain", "TI"), Global.newObject("deviceFamily", "ARM", "toolChain", "TI"), Global.newObject("deviceFamily", "C2000", "toolChain", "TI")}), "requiredProducts", Global.newArray(new Object[]{"com.ti.rtsc.SYSBIOS", "com.ti.rtsc.IPC"}), "linkerCommandFile", ""), Global.newObject("title", "Stairstep Simulator", "fileList", Global.newArray(new Object[]{Global.newObject("path", "./single/stairstep.c"), Global.newObject("path", "./single/stairstep_Simulator.cfg")}), "description", "The stairstep example runs continusously and periodically generates log events. Different threads (Hwi, Swi, Task) run to present a CPU load to the system.\\n\\nThe Log data is obtained by temporarily stopping the target when the Log call is made.\\n\\nThe sizes of the loggers in LoggingSetup might need to be decreased if your target does not have enough memory\\n\\nTo build this example, the XDC version must be 3.22 (or later) or the RTSC Build-Profile must be \"release\" or \"debug\" (not \"whole_program\").", "buildProfile", "release", "groups", Global.newArray(new Object[]{"ti.uia.examples.root.level1"}), "isHybrid", true, "filterArr", Global.newArray(new Object[]{Global.newObject("deviceFamily", "C6000", "toolChain", "TI"), Global.newObject("deviceFamily", "ARM", "toolChain", "TI"), Global.newObject("deviceFamily", "C2000", "toolChain", "TI")}), "requiredProducts", Global.newArray(new Object[]{"com.ti.rtsc.SYSBIOS", "com.ti.rtsc.IPC"}), "linkerCommandFile", ""), Global.newObject("title", "evmti816x: SimpleTask w/ LoggerCircBuf for the DSP", "fileList", Global.newArray(new Object[]{Global.newObject("path", "./evmti816x/simpleTask.c"), Global.newObject("path", "./evmti816x/dspLoggerCircBuf.cfg")}), "description", "This DSP example uses LoggerCircBuf to log benchmark events. The events are routed through the ServiceMgr on Linux.\\n\\nThe program benchmarks the duration to run an \"algorithm\"\\n\\nRefer to the Getting Started Guide for a more detailed description.", "groups", Global.newArray(new Object[]{"ti.uia.examples.root.level2"}), "buildProfile", "release", "platform", "ti.uia.examples.platforms.evmTI816X.dsp", "isHybrid", true, "filterArr", Global.newArray(new Object[]{Global.newObject("deviceFamily", "C6000", "toolChain", "TI")}), "requiredProducts", Global.newArray(new Object[]{"com.ti.rtsc.SYSBIOS", "com.ti.rtsc.IPC"}), "linkerCommandFile", ""), Global.newObject("title", "evmti816x: SimpleTask w/ LoggerSM for the DSP", "fileList", Global.newArray(new Object[]{Global.newObject("path", "./evmti816x/simpleTask.c"), Global.newObject("path", "./evmti816x/dspLoggerSM.cfg")}), "description", "This DSP example uses LoggerSM to log benchmark events. The events can be displayed to the Linux console or written to a binary file.\\n\\nThe program benchmarks the duration to run an \"algorithm\"\\n\\nRefer to the Getting Started Guide for a more detailed description.", "groups", Global.newArray(new Object[]{"ti.uia.examples.root.level2"}), "buildProfile", "release", "platform", "ti.uia.examples.platforms.evmTI816X.dsp", "isHybrid", true, "filterArr", Global.newArray(new Object[]{Global.newObject("deviceFamily", "C6000", "toolChain", "TI")}), "requiredProducts", Global.newArray(new Object[]{"com.ti.rtsc.SYSBIOS", "com.ti.rtsc.IPC"}), "linkerCommandFile", ""), Global.newObject("title", "evmti816x: SimpleTask w/ LoggerCircBuf for the video M3", "fileList", Global.newArray(new Object[]{Global.newObject("path", "./evmti816x/simpleTask.c"), Global.newObject("path", "./evmti816x/videoM3LoggerCircBuf.cfg")}), "description", "This Video M3 example uses LoggerCircBuf to log benchmark events. The events are routed through the ServiceMgr on Linux.\\n\\nThe program benchmarks the duration to run an \"algorithm\"\\n\\nRefer to the Getting Started Guide for a more detailed description.", "groups", Global.newArray(new Object[]{"ti.uia.examples.root.level2"}), "buildProfile", "release", "platform", "ti.uia.examples.platforms.evmTI816X.video", "isHybrid", true, "filterArr", Global.newArray(new Object[]{Global.newObject("deviceFamily", "ARM", "toolChain", "TI")}), "requiredProducts", Global.newArray(new Object[]{"com.ti.rtsc.SYSBIOS", "com.ti.rtsc.IPC"}), "linkerCommandFile", ""), Global.newObject("title", "evmti816x: SimpleTask w/ LoggerCircBuf for the vpss M3", "fileList", Global.newArray(new Object[]{Global.newObject("path", "./evmti816x/simpleTask.c"), Global.newObject("path", "./evmti816x/vpssM3LoggerCircBuf.cfg")}), "description", "This VPSS M3 example uses LoggerCircBuf to log benchmark events. The events are routed through the ServiceMgr on Linux.\\n\\nThe program benchmarks the duration to run an \"algorithm\"\\n\\nRefer to the Getting Started Guide for a more detailed description.", "groups", Global.newArray(new Object[]{"ti.uia.examples.root.level2"}), "buildProfile", "release", "platform", "ti.uia.examples.platforms.evmTI816X.vpss", "isHybrid", true, "filterArr", Global.newArray(new Object[]{Global.newObject("deviceFamily", "ARM", "toolChain", "TI")}), "requiredProducts", Global.newArray(new Object[]{"com.ti.rtsc.SYSBIOS", "com.ti.rtsc.IPC"}), "linkerCommandFile", ""), Global.newObject("title", "evmti816x: SimpleTask w/ LoggerSM for the video M3", "fileList", Global.newArray(new Object[]{Global.newObject("path", "./evmti816x/simpleTask.c"), Global.newObject("path", "./evmti816x/videoM3LoggerSM.cfg")}), "description", "This Video M3 example uses LoggerSM to log benchmark events. The events can be displayed to the Linux console or written to a binary file.\\n\\nThe program benchmarks the duration to run an \"algorithm\"\\n\\nRefer to the Getting Started Guide for a more detailed description.", "groups", Global.newArray(new Object[]{"ti.uia.examples.root.level2"}), "buildProfile", "release", "platform", "ti.uia.examples.platforms.evmTI816X.video", "isHybrid", true, "filterArr", Global.newArray(new Object[]{Global.newObject("deviceFamily", "ARM", "toolChain", "TI")}), "requiredProducts", Global.newArray(new Object[]{"com.ti.rtsc.SYSBIOS", "com.ti.rtsc.IPC"}), "linkerCommandFile", ""), Global.newObject("title", "evmti816x: SimpleTask w/ LoggerSM for the vpss M3", "fileList", Global.newArray(new Object[]{Global.newObject("path", "./evmti816x/simpleTask.c"), Global.newObject("path", "./evmti816x/vpssM3LoggerSM.cfg")}), "description", "This VPSS M3 example uses LoggerSM to log benchmark events. The events can be displayed to the Linux console or written to a binary file.\\n\\nThe program benchmarks the duration to run an \"algorithm\"\\n\\nRefer to the Getting Started Guide for a more detailed description.", "groups", Global.newArray(new Object[]{"ti.uia.examples.root.level2"}), "buildProfile", "release", "platform", "ti.uia.examples.platforms.evmTI816X.vpss", "isHybrid", true, "filterArr", Global.newArray(new Object[]{Global.newObject("deviceFamily", "ARM", "toolChain", "TI")}), "requiredProducts", Global.newArray(new Object[]{"com.ti.rtsc.SYSBIOS", "com.ti.rtsc.IPC"}), "linkerCommandFile", ""), Global.newObject("title", "System Analyzer and UIA Tutorial 1: Logging events, benchmarking, controlling events.", "fileList", Global.newArray(new Object[]{Global.newObject("path", "./tutorial1/main.c"), Global.newObject("path", "./tutorial1/tutorial1a.c"), Global.newObject("path", "./tutorial1/tutorial1b.c"), Global.newObject("path", "./tutorial1/tutorial1c.c"), Global.newObject("path", "./tutorial1/tutorial1d.c"), Global.newObject("path", "./tutorial1/systemAnalyzerTutorial1.gel"), Global.newObject("path", "./tutorial1/systemAnalyzerTutorial1.cfg")}), "description", "This tutorial shows how to log errors, warnings and info events, benchmark code and control which events are logged. Refer to http://processors.wiki.ti.com/index.php/McsaTutorial1 for more details.", "groups", Global.newArray(new Object[]{"ti.uia.examples.root.level3"}), "buildProfile", "release", "isHybrid", true, "filterArr", Global.newArray(new Object[]{Global.newObject("deviceFamily", "C6000", "toolChain", "TI"), Global.newObject("deviceFamily", "ARM", "toolChain", "TI"), Global.newObject("deviceFamily", "C2000", "toolChain", "TI")}), "requiredProducts", Global.newArray(new Object[]{}), "linkerCommandFile", ""), Global.newObject("title", "System Analyzer and UIA Tutorial 2: Graphing events, using JTAG Run-Mode (C64X+ or C66X emulation target)", "fileList", Global.newArray(new Object[]{Global.newObject("path", "./tutorial2/main.c"), Global.newObject("path", "./tutorial2/systemAnalyzerTutorial2.gel"), Global.newObject("path", "./tutorial2/systemAnalyzerTutorial2.cfg")}), "description", "This tutorial shows how to log data that can be graphed and analyzed for min/max/average statistics.  Also demonstrates how to use LoggerCircBuf and JTAG Run-Mode to upload events while a target is running . Refer to http://processors.wiki.ti.com/index.php/McsaTutorial2 for more details.", "groups", Global.newArray(new Object[]{"ti.uia.examples.root.level3"}), "buildProfile", "release", "isHybrid", true, "filterArr", Global.newArray(new Object[]{Global.newObject("deviceFamily", "C6000", "toolChain", "TI")}), "requiredProducts", Global.newArray(new Object[]{}), "linkerCommandFile", "")}), "wh");
    }

    void Examples$$ROV()
    {
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.uia.examples.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.uia.examples"));
        pkgP.bind("$capsule", $$UNDEF);
        pkgV.init2(pkgP, "ti.uia.examples", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.uia.examples");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.uia.examples.");
        pkgV.bind("$vers", Global.newArray());
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.uia.examples'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
        sb.append("];\n");
        Global.eval(sb.toString());
    }

    void Examples$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.uia.examples.Examples", "ti.uia.examples");
        po = (Proto.Obj)om.findStrict("ti.uia.examples.Examples.Module", "ti.uia.examples");
        vo.init2(po, "ti.uia.examples.Examples", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", $$UNDEF);
        vo.bind("$package", om.findStrict("ti.uia.examples", "ti.uia.examples"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        icfgs.clear();
        inherits.clear();
        vo.bind("FileDesc", om.findStrict("xdc.tools.product.IProductTemplate.FileDesc", "ti.uia.examples"));
        tdefs.add(om.findStrict("xdc.tools.product.IProductTemplate.FileDesc", "ti.uia.examples"));
        vo.bind("Filter", om.findStrict("xdc.tools.product.IProductTemplate.Filter", "ti.uia.examples"));
        tdefs.add(om.findStrict("xdc.tools.product.IProductTemplate.Filter", "ti.uia.examples"));
        vo.bind("TemplateInfo", om.findStrict("xdc.tools.product.IProductTemplate.TemplateInfo", "ti.uia.examples"));
        tdefs.add(om.findStrict("xdc.tools.product.IProductTemplate.TemplateInfo", "ti.uia.examples"));
        vo.bind("TemplateGroup", om.findStrict("xdc.tools.product.IProductTemplate.TemplateGroup", "ti.uia.examples"));
        tdefs.add(om.findStrict("xdc.tools.product.IProductTemplate.TemplateGroup", "ti.uia.examples"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("xdc.tools.product");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.uia.examples")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.uia.examples.Examples$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        pkgV.bind("Examples", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Examples");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.uia.examples.Examples", "ti.uia.examples"));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.uia.examples.Examples")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.uia.examples")).add(pkgV);
    }

    public void exec( Scriptable xdcO, Session ses )
    {
        this.xdcO = xdcO;
        this.ses = ses;
        om = (Value.Obj)xdcO.get("om", null);

        Object o = om.geto("$name");
        String s = o instanceof String ? (String)o : null;
        isCFG = s != null && s.equals("cfg");
        isROV = s != null && s.equals("rov");

        $$IMPORTS();
        $$OBJECTS();
        Examples$$OBJECTS();
        Examples$$CONSTS();
        Examples$$CREATES();
        Examples$$FUNCTIONS();
        Examples$$SIZES();
        Examples$$TYPES();
        if (isROV) {
            Examples$$ROV();
        }//isROV
        $$SINGLETONS();
        Examples$$SINGLETONS();
        $$INITIALIZATION();
    }
}
