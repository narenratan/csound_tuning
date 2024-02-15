/*

Csound opcodes for microtonal tunings.

    * scalatuning: loads tunings from scl and kbm files
    * mtsesp_notetofrequency: queries tunings with MTS-ESP

*/
#include <string>
#include <csdl.h>
#include <arrays.h>
#include "Tunings.h"
#include "libMTSClient.h"

#define MTSESP_CLIENT_VARNAME "__mtsesp_client__"

typedef struct
{
    OPDS h;
    ARRAYDAT *out;
    STRINGDAT *in1, *in2;
} SCALATUNING;

int scalatuning(CSOUND *csound, SCALATUNING *p)
{
    tabinit(csound, p->out, 128);
    auto s = Tunings::readSCLFile(p->in1->data);
    Tunings::Tuning t;
    if (*p->in2->data)
    {
        auto k = Tunings::readKBMFile(p->in2->data);
        t = Tunings::Tuning(s, k);
    }
    else
    {
        t = Tunings::Tuning(s);
    }

    for (int i = 0; i < 128; i++)
    {
        p->out->data[i] = t.frequencyForMidiNote(i);
    }
    return OK;
}

MTSClient *get_mtsesp_client(CSOUND *csound)
{
    return *(MTSClient **)csound->QueryGlobalVariable(csound, MTSESP_CLIENT_VARNAME);
}

typedef struct
{
    OPDS h;
    MYFLT *out;
    MYFLT *in1, *in2;
} MTSESP_NOTETOFREQUENCY;

int mtsesp_notetofrequency(CSOUND *csound, MTSESP_NOTETOFREQUENCY *p)
{
    MTSClient *client = get_mtsesp_client(csound);
    *p->out = MTS_NoteToFrequency(client, *p->in1, *p->in2);
    return OK;
}

static OENTRY localops[] = {
    {"scalatuning", sizeof(SCALATUNING), 0, 1, "i[]", "SS", (SUBR)scalatuning, NULL},
    {"mtsesp_notetofrequency", sizeof(MTSESP_NOTETOFREQUENCY), 0, 1, "i", "io",
     (SUBR)mtsesp_notetofrequency, NULL},
    {"mtsesp_notetofrequency", sizeof(MTSESP_NOTETOFREQUENCY), 0, 2, "k", "ko", NULL,
     (SUBR)mtsesp_notetofrequency},
};

PUBLIC int csoundModuleCreate(CSOUND *csound)
{
    int err = csound->CreateGlobalVariable(csound, MTSESP_CLIENT_VARNAME, sizeof(MTSClient *));
    if (err != 0)
    {
        csound->Message(csound, Str("Failed to allocate global for MTS-ESP client\n"));
        return 1;
    };
    MTSClient **client_global =
        (MTSClient **)csound->QueryGlobalVariable(csound, MTSESP_CLIENT_VARNAME);
    *client_global = MTS_RegisterClient();
    return 0;
}

PUBLIC int csoundModuleInit(CSOUND *csound)
{
    int status = 0;
    for (OENTRY *oentry = &localops[0]; oentry->opname; oentry++)
    {
        status |= csound->AppendOpcode(
            csound, oentry->opname, oentry->dsblksiz, oentry->flags, oentry->thread,
            oentry->outypes, oentry->intypes, (int (*)(CSOUND *, void *))oentry->iopadr,
            (int (*)(CSOUND *, void *))oentry->kopadr, (int (*)(CSOUND *, void *))oentry->aopadr);
    }
    return status;
}

PUBLIC int csoundModuleDestroy(CSOUND *csound)
{
    MTSClient *client = get_mtsesp_client(csound);
    MTS_DeregisterClient(client);
    return 0;
}

LINKAGE
