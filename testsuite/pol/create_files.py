'''
Quick and dirty prototype implement in poltool?
'''
import struct
import os


class TiledataItem:
    def __init__(self):
        self.flags=1
        self.hsaflags=0
        self.weight=0
        self.layer=0
        self.unk1=0
        self.anim=0
        self.unk2=0
        self.height=0
        self.name=''
    def pack(self, stream, hsa):
        if hsa:
            stream.write(
                struct.pack( '<IIBBIIHB20s',
                    self.flags,
                    self.hsaflags,
                    self.weight,
                    self.layer,
                    self.unk1,
                    self.anim,
                    self.unk2,
                    self.height,
                    str.encode(self.name)
                )
            )
        else:
            stream.write(
                struct.pack( '<IBBIIHB20s',
                    self.flags,
                    self.weight,
                    self.layer,
                    self.unk1,
                    self.anim,
                    self.unk2,
                    self.height,
                    str.encode(self.name)
                )
            )
class TiledataLand:
    def __init__(self):
        self.flags=1
        self.hsaflags=0
        self.unk1=0
        self.name='h'
    def pack(self, stream, hsa):
        if hsa:
            stream.write(
                struct.pack( '<IIH20s',
                    self.flags,
                    self.hsaflags,
                    self.unk1,
                   str.encode(self.name)
               )
            )
        else:
            stream.write(
                struct.pack( '<IH20s',
                    self.flags,
                    self.unk1,
                   str.encode(self.name)
               )
            )

def generate_tiledata(path, hsa, maxtile):
    with open(os.path.join(path,'tiledata.mul'),'wb') as f:
        land=[TiledataLand() for i in range(0x4000)]
        item=[TiledataItem() for i in range(maxtile+1)]
        land[0].name = 'hallo12345hallo12345'
        land[31].name = 'hallo12345hallo12345hallo'
        land[64].name = 'hallo12345hallo12345hallo'
        item[0].name = 'hallo1'
        item[-1].name = 'hallo'
        item[-1].flags=1
        item[-1].weight=2
        item[-1].layer=3
        item[-1].unk1=4
        item[-1].anim=5
        item[-1].unk2=6
        item[-1].height=1
        for i,e in enumerate(land):
            if (i & 0x1f)==0:
                f.write(struct.pack('<I',0))
            e.pack(f,hsa)
        for i,e in enumerate(item):
            if (i & 0x1f)==0:
                f.write(struct.pack('<I',0))
            e.pack(f,hsa)


class MapTile():
    def __init__(self,tile,z):
        self.tile=tile
        self.z=z
        self.p=struct.pack( '<Hb',
                self.tile,
                self.z
            )
    def pack(self, stream):
        stream.write(self.p)

def generate_map(path,width,height):
    default=MapTile(0,0)
    mod={
            (0,0):MapTile(1,10),
        }
    m=mod.get((0,0),default)
    header=struct.pack('<I',0)
    with open(os.path.join(path,'map0.mul'),'wb') as f:
        for x in range(width//8):
            for y in range(height//8):
                f.write(header)
                for ix in range(8):
                    for iy in range(8):
                        t=mod.get((x*8+ix,y*8+iy),default)
                        t.pack(f)

def generate_statics(path,width,height):
    with open(os.path.join(path,'statics0.mul'),'wb') as f:
        pass
    with open(os.path.join(path,'staidx0.mul'),'wb') as f:
        entry=struct.pack('<iii',-1,-1,-1)
        for x in range(width//8):
            for y in range(height//8):
                f.write(entry)



generate_map('.',6144,4096)
generate_statics('.',6144,4096)
generate_tiledata('.', False, 0x3Fff)
