﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Agemarker
{
    public partial class Data
    {
        public enum CalculationStatus { Waiting, Running, Paused, Finished }

        public static string[,] ElementsName = new string[118, 2];
        public static double[] ElementsWeight = new double[118];
        public static string[,] OxidesName = new string[53, 2];

        public static void LoadData()
        {
            #region ElementsName
            ElementsName[0, 0] = "H";
            ElementsName[0, 1] = "Hydrogene";
            ElementsName[1, 0] = "He";
            ElementsName[1, 1] = "Helium";
            ElementsName[2, 0] = "Li";
            ElementsName[2, 1] = "Lithium";
            ElementsName[3, 0] = "Be";
            ElementsName[3, 1] = "Beryllium";
            ElementsName[4, 0] = "B";
            ElementsName[4, 1] = "Boron";
            ElementsName[5, 0] = "C";
            ElementsName[5, 1] = "Carbon";
            ElementsName[6, 0] = "N";
            ElementsName[6, 1] = "Nitrogen";
            ElementsName[7, 0] = "O";
            ElementsName[7, 1] = "Oxygen";
            ElementsName[8, 0] = "F";
            ElementsName[8, 1] = "Fluorine";
            ElementsName[9, 0] = "Ne";
            ElementsName[9, 1] = "Neon";
            ElementsName[10, 0] = "Na";
            ElementsName[10, 1] = "Sodium";
            ElementsName[11, 0] = "Mg";
            ElementsName[11, 1] = "Magnesium";
            ElementsName[12, 0] = "Al";
            ElementsName[12, 1] = "Aluminium";
            ElementsName[13, 0] = "Si";
            ElementsName[13, 1] = "Silicon";
            ElementsName[14, 0] = "P";
            ElementsName[14, 1] = "Phosphorus";
            ElementsName[15, 0] = "S";
            ElementsName[15, 1] = "Sulfur";
            ElementsName[16, 0] = "Cl";
            ElementsName[16, 1] = "Chlorine";
            ElementsName[17, 0] = "Ar";
            ElementsName[17, 1] = "Argon";
            ElementsName[18, 0] = "K";
            ElementsName[18, 1] = "Potassium";
            ElementsName[19, 0] = "Ca";
            ElementsName[19, 1] = "Calcium";
            ElementsName[20, 0] = "Sc";
            ElementsName[20, 1] = "Scandium";
            ElementsName[21, 0] = "Ti";
            ElementsName[21, 1] = "Titanium";
            ElementsName[22, 0] = "V";
            ElementsName[22, 1] = "Vanadium";
            ElementsName[23, 0] = "Cr";
            ElementsName[23, 1] = "Chromium";
            ElementsName[24, 0] = "Mn";
            ElementsName[24, 1] = "Manganese";
            ElementsName[25, 0] = "Fe";
            ElementsName[25, 1] = "Iron";
            ElementsName[26, 0] = "Co";
            ElementsName[26, 1] = "Cobalt";
            ElementsName[27, 0] = "Ni";
            ElementsName[27, 1] = "Nickel";
            ElementsName[28, 0] = "Cu";
            ElementsName[28, 1] = "Copper";
            ElementsName[29, 0] = "Zn";
            ElementsName[29, 1] = "Zinc";
            ElementsName[30, 0] = "Ga";
            ElementsName[30, 1] = "Gallium";
            ElementsName[31, 0] = "Ge";
            ElementsName[31, 1] = "Germanium";
            ElementsName[32, 0] = "As";
            ElementsName[32, 1] = "Arsenic";
            ElementsName[33, 0] = "Se";
            ElementsName[33, 1] = "Selenium";
            ElementsName[34, 0] = "Br";
            ElementsName[34, 1] = "Bromine";
            ElementsName[35, 0] = "Kr";
            ElementsName[35, 1] = "Krypton";
            ElementsName[36, 0] = "Rb";
            ElementsName[36, 1] = "Rubidium";
            ElementsName[37, 0] = "Sr";
            ElementsName[37, 1] = "Strontium";
            ElementsName[38, 0] = "Y";
            ElementsName[38, 1] = "Yttrium";
            ElementsName[39, 0] = "Zr";
            ElementsName[39, 1] = "Zirconium";
            ElementsName[40, 0] = "Nb";
            ElementsName[40, 1] = "Niobium";
            ElementsName[41, 0] = "Mo";
            ElementsName[41, 1] = "Molybdenum";
            ElementsName[42, 0] = "Tc";
            ElementsName[42, 1] = "Technetium";
            ElementsName[43, 0] = "Ru";
            ElementsName[43, 1] = "Ruthenium";
            ElementsName[44, 0] = "Rh";
            ElementsName[44, 1] = "Rhodium";
            ElementsName[45, 0] = "Pd";
            ElementsName[45, 1] = "Palladium";
            ElementsName[46, 0] = "Ag";
            ElementsName[46, 1] = "Silver";
            ElementsName[47, 0] = "Cd";
            ElementsName[47, 1] = "Cadmium";
            ElementsName[48, 0] = "In";
            ElementsName[48, 1] = "Indium";
            ElementsName[49, 0] = "Sn";
            ElementsName[49, 1] = "Tin";
            ElementsName[50, 0] = "Sb";
            ElementsName[50, 1] = "Antimony";
            ElementsName[51, 0] = "Te";
            ElementsName[51, 1] = "Tellurium";
            ElementsName[52, 0] = "I";
            ElementsName[52, 1] = "Iodime";
            ElementsName[53, 0] = "Xe";
            ElementsName[53, 1] = "Xenon";
            ElementsName[54, 0] = "Cs";
            ElementsName[54, 1] = "Caesium";
            ElementsName[55, 0] = "Ba";
            ElementsName[55, 1] = "Barium";
            ElementsName[56, 0] = "La";
            ElementsName[56, 1] = "Lanthanum";
            ElementsName[57, 0] = "Ce";
            ElementsName[57, 1] = "Cerium";
            ElementsName[58, 0] = "Pr";
            ElementsName[58, 1] = "Praseodymium";
            ElementsName[59, 0] = "Nd";
            ElementsName[59, 1] = "Neodymium";
            ElementsName[60, 0] = "Pm";
            ElementsName[60, 1] = "Promethium";
            ElementsName[61, 0] = "Sm";
            ElementsName[61, 1] = "Samarium";
            ElementsName[62, 0] = "Eu";
            ElementsName[62, 1] = "Europium";
            ElementsName[63, 0] = "Gd";
            ElementsName[63, 1] = "Gadolinium";
            ElementsName[64, 0] = "Tb";
            ElementsName[64, 1] = "Terbium";
            ElementsName[65, 0] = "Dy";
            ElementsName[65, 1] = "Dysprosium";
            ElementsName[66, 0] = "Ho";
            ElementsName[66, 1] = "Holmium";
            ElementsName[67, 0] = "Er";
            ElementsName[67, 1] = "Erbium";
            ElementsName[68, 0] = "Tm";
            ElementsName[68, 1] = "Thulium";
            ElementsName[69, 0] = "Yb";
            ElementsName[69, 1] = "Ytterbium";
            ElementsName[70, 0] = "Lu";
            ElementsName[70, 1] = "Lutetium";
            ElementsName[71, 0] = "Hf";
            ElementsName[71, 1] = "Hafnium";
            ElementsName[72, 0] = "Ta";
            ElementsName[72, 1] = "Tantalum";
            ElementsName[73, 0] = "W";
            ElementsName[73, 1] = "Tungsten";
            ElementsName[74, 0] = "Re";
            ElementsName[74, 1] = "Rhenium";
            ElementsName[75, 0] = "Os";
            ElementsName[75, 1] = "Osmium";
            ElementsName[76, 0] = "Ir";
            ElementsName[76, 1] = "Iridium";
            ElementsName[77, 0] = "Pt";
            ElementsName[77, 1] = "Platinum";
            ElementsName[78, 0] = "Au";
            ElementsName[78, 1] = "Gold";
            ElementsName[79, 0] = "Hg";
            ElementsName[79, 1] = "Mercury";
            ElementsName[80, 0] = "Tl";
            ElementsName[80, 1] = "Thalium";
            ElementsName[81, 0] = "Pb";
            ElementsName[81, 1] = "Lead";
            ElementsName[82, 0] = "Bi";
            ElementsName[82, 1] = "Bismuth";
            ElementsName[83, 0] = "Po";
            ElementsName[83, 1] = "Polonium";
            ElementsName[84, 0] = "At";
            ElementsName[84, 1] = "Astatine";
            ElementsName[85, 0] = "Rn";
            ElementsName[85, 1] = "Radon";
            ElementsName[86, 0] = "Fr";
            ElementsName[86, 1] = "Francium";
            ElementsName[87, 0] = "Ra";
            ElementsName[87, 1] = "Radium";
            ElementsName[88, 0] = "Ac";
            ElementsName[88, 1] = "Actinum";
            ElementsName[89, 0] = "Th";
            ElementsName[89, 1] = "Thorium";
            ElementsName[90, 0] = "Pa";
            ElementsName[90, 1] = "Protactinium";
            ElementsName[91, 0] = "U";
            ElementsName[91, 1] = "Uranium";
            ElementsName[92, 0] = "Np";
            ElementsName[92, 1] = "Neptunium";
            ElementsName[93, 0] = "Pu";
            ElementsName[93, 1] = "Plutonium";
            ElementsName[94, 0] = "Am";
            ElementsName[94, 1] = "Americium";
            ElementsName[95, 0] = "Cm";
            ElementsName[95, 1] = "Curium";
            ElementsName[96, 0] = "Bk";
            ElementsName[96, 1] = "Berkelium";
            ElementsName[97, 0] = "Cf";
            ElementsName[97, 1] = "Californium";
            ElementsName[98, 0] = "Es";
            ElementsName[98, 1] = "Einsteinium";
            ElementsName[99, 0] = "Fm";
            ElementsName[99, 1] = "Fermium";
            ElementsName[100, 0] = "Md";
            ElementsName[100, 1] = "Mendelevium";
            ElementsName[101, 0] = "No";
            ElementsName[101, 1] = "Nobelium";
            ElementsName[102, 0] = "Lr";
            ElementsName[102, 1] = "Lawrencium";
            ElementsName[103, 0] = "Rf";
            ElementsName[103, 1] = "Rutherfordium";
            ElementsName[104, 0] = "Db";
            ElementsName[104, 1] = "Dubnium";
            ElementsName[105, 0] = "Sg";
            ElementsName[105, 1] = "Seaborgium";
            ElementsName[106, 0] = "Bh";
            ElementsName[106, 1] = "Bohrium";
            ElementsName[107, 0] = "Hs";
            ElementsName[107, 1] = "Hassium";
            ElementsName[108, 0] = "Mt";
            ElementsName[108, 1] = "Meitnerium";
            ElementsName[109, 0] = "Ds";
            ElementsName[109, 1] = "Darmstadtium";
            ElementsName[110, 0] = "Rg";
            ElementsName[110, 1] = "Roentgenium";
            ElementsName[111, 0] = "Cn";
            ElementsName[111, 1] = "Copernicium";
            ElementsName[112, 0] = "Uut";
            ElementsName[112, 1] = "Ununtrium";
            ElementsName[113, 0] = "Fl";
            ElementsName[113, 1] = "Flerovium";
            ElementsName[114, 0] = "Uup";
            ElementsName[114, 1] = "Ununpentium";
            ElementsName[115, 0] = "Lv";
            ElementsName[115, 1] = "Livermorium";
            ElementsName[116, 0] = "Uus";
            ElementsName[116, 1] = "Ununseptium";
            ElementsName[117, 0] = "Uuo";
            ElementsName[117, 1] = "Ununoctium";
            #endregion
            #region ElementsWeight
            ElementsWeight[0] = 1.008;
            ElementsWeight[1] = 4.002602;
            ElementsWeight[2] = 6.94;
            ElementsWeight[3] = 9.012182;
            ElementsWeight[4] = 10.81;
            ElementsWeight[5] = 12.011;
            ElementsWeight[6] = 14.007;
            ElementsWeight[7] = 15.999;
            ElementsWeight[8] = 18.9984032;
            ElementsWeight[9] = 20.1797;
            ElementsWeight[10] = 22.98976928;
            ElementsWeight[11] = 24.3050;
            ElementsWeight[12] = 26.9815386;
            ElementsWeight[13] = 28.085;
            ElementsWeight[14] = 30.973762;
            ElementsWeight[15] = 32.06;
            ElementsWeight[16] = 35.45;
            ElementsWeight[17] = 39.948;
            ElementsWeight[18] = 39.0983;
            ElementsWeight[19] = 40.078;
            ElementsWeight[20] = 44.955912;
            ElementsWeight[21] = 47.867;
            ElementsWeight[22] = 50.9415;
            ElementsWeight[23] = 51.9961;
            ElementsWeight[24] = 54.938045;
            ElementsWeight[25] = 55.845;
            ElementsWeight[26] = 58.933195;
            ElementsWeight[27] = 58.6934;
            ElementsWeight[28] = 63.546;
            ElementsWeight[29] = 65.38;
            ElementsWeight[30] = 69.723;
            ElementsWeight[31] = 72.63;
            ElementsWeight[32] = 74.92160;
            ElementsWeight[33] = 78.96;
            ElementsWeight[34] = 79.904;
            ElementsWeight[35] = 83.798;
            ElementsWeight[36] = 85.4678;
            ElementsWeight[37] = 87.62;
            ElementsWeight[38] = 88.90585;
            ElementsWeight[39] = 91.224;
            ElementsWeight[40] = 92.90638;
            ElementsWeight[41] = 95.96;
            ElementsWeight[42] = 97.91;
            ElementsWeight[43] = 101.07;
            ElementsWeight[44] = 102.90550;
            ElementsWeight[45] = 106.42;
            ElementsWeight[46] = 107.8682;
            ElementsWeight[47] = 112.411;
            ElementsWeight[48] = 114.818;
            ElementsWeight[49] = 118.710;
            ElementsWeight[50] = 121.760;
            ElementsWeight[51] = 127.60;
            ElementsWeight[52] = 126.90447;
            ElementsWeight[53] = 131.293;
            ElementsWeight[54] = 132.9054519;
            ElementsWeight[55] = 137.327;
            ElementsWeight[56] = 138.90547;
            ElementsWeight[57] = 140.116;
            ElementsWeight[58] = 140.90765;
            ElementsWeight[59] = 144.242;
            ElementsWeight[60] = 144.91;
            ElementsWeight[61] = 150.36;
            ElementsWeight[62] = 151.964;
            ElementsWeight[63] = 157.25;
            ElementsWeight[64] = 158.92535;
            ElementsWeight[65] = 162.500;
            ElementsWeight[66] = 164.93032;
            ElementsWeight[67] = 167.259;
            ElementsWeight[68] = 168.93421;
            ElementsWeight[69] = 173.054;
            ElementsWeight[70] = 174.9668;
            ElementsWeight[71] = 178.49;
            ElementsWeight[72] = 180.94788;
            ElementsWeight[73] = 183.84;
            ElementsWeight[74] = 186.207;
            ElementsWeight[75] = 190.23;
            ElementsWeight[76] = 192.217;
            ElementsWeight[77] = 195.084;
            ElementsWeight[78] = 196.966569;
            ElementsWeight[79] = 200.59;
            ElementsWeight[80] = 204.38;
            ElementsWeight[81] = 207.2;
            ElementsWeight[82] = 208.98040;
            ElementsWeight[83] = 209;
            ElementsWeight[84] = 210;
            ElementsWeight[85] = 222;
            ElementsWeight[86] = 223.02;
            ElementsWeight[87] = 226.03;
            ElementsWeight[88] = 227.03;
            ElementsWeight[89] = 232.03806;
            ElementsWeight[90] = 231.03588;
            ElementsWeight[91] = 238.02891;
            ElementsWeight[92] = 237.05;
            ElementsWeight[93] = 244.06;
            ElementsWeight[94] = 243.06;
            ElementsWeight[95] = 247.07;
            ElementsWeight[96] = 247.07;
            ElementsWeight[97] = 251.08;
            ElementsWeight[98] = 252.08;
            ElementsWeight[99] = 257.10;
            ElementsWeight[100] = 258.10;
            ElementsWeight[101] = 259.10;
            ElementsWeight[102] = 262.11;
            ElementsWeight[103] = 265.12;
            ElementsWeight[104] = 268.13;
            ElementsWeight[105] = 271.13;
            ElementsWeight[106] = 207;
            ElementsWeight[107] = 277.15;
            ElementsWeight[108] = 276.15;
            ElementsWeight[109] = 281.16;
            ElementsWeight[110] = 280.16;
            ElementsWeight[111] = 285.17;
            ElementsWeight[112] = 284.18;
            ElementsWeight[113] = 289.19;
            ElementsWeight[114] = 288.19;
            ElementsWeight[115] = 293;
            ElementsWeight[116] = 294;
            ElementsWeight[117] = 294;
            #endregion
            #region OxidesName
            OxidesName[0, 0] = "SiO2";
            OxidesName[0, 1] = "Silicon dioxide";
            OxidesName[1, 0] = "TiO2";
            OxidesName[1, 1] = "Titanium dioxide";
            OxidesName[2, 0] = "Al2O3";
            OxidesName[2, 1] = "Aluminium oxide";
            OxidesName[3, 0] = "Fe2O3";
            OxidesName[3, 1] = "Ferric oxide";
            OxidesName[4, 0] = "FeO";
            OxidesName[4, 1] = "Ferrous oxide";
            OxidesName[5, 0] = "MnO";
            OxidesName[5, 1] = "Manganese(II) oxide";
            OxidesName[6, 0] = "MgO";
            OxidesName[6, 1] = "Magnesium oxide";
            OxidesName[7, 0] = "K2O";
            OxidesName[7, 1] = "Potassium oxide";
            OxidesName[8, 0] = "CaO";
            OxidesName[8, 1] = "Calcium oxide";
            OxidesName[9, 0] = "Na2O";
            OxidesName[9, 1] = "Sodium oxide";
            OxidesName[10, 0] = "H2O-";
            OxidesName[10, 1] = "Water";
            OxidesName[11, 0] = "H2O+";
            OxidesName[11, 1] = "Water";
            OxidesName[12, 0] = "P2O5";
            OxidesName[12, 1] = "Phosphorus pentoxide";
            OxidesName[13, 0] = "CO2";
            OxidesName[13, 1] = "Carbon dioxide";
            OxidesName[14, 0] = "B2O3";
            OxidesName[14, 1] = "Boron trioxide";
            OxidesName[15, 0] = "SO3";
            OxidesName[15, 1] = "Sulfur trioxide";
            OxidesName[16, 0] = "V2O5";
            OxidesName[16, 1] = "Vanadium pentoxide";
            OxidesName[17, 0] = "Cr2O3";
            OxidesName[17, 1] = "Chromium(III) oxide";
            OxidesName[18, 0] = "NiO";
            OxidesName[18, 1] = "Nickel(II) oxide";
            OxidesName[19, 0] = "As2O3";
            OxidesName[19, 1] = "Arsenic trioxide ";
            OxidesName[20, 0] = "Y2O3";
            OxidesName[20, 1] = "Yttrium oxide";
            OxidesName[21, 0] = "BaO";
            OxidesName[21, 1] = "Barium oxide";
            OxidesName[22, 0] = "La2O3";
            OxidesName[22, 1] = "Lanthanum oxide";
            OxidesName[23, 0] = "CeO2";
            OxidesName[23, 1] = "Cerium(IV) oxide";
            OxidesName[24, 0] = "Pr2O3";
            OxidesName[24, 1] = "Praseodymium(III) oxide";
            OxidesName[25, 0] = "Nd2O3";
            OxidesName[25, 1] = "Neodymium(III) oxide";
            OxidesName[26, 0] = "Sm2O3";
            OxidesName[26, 1] = "Samarium(III) oxide";
            OxidesName[27, 0] = "Eu2O3";
            OxidesName[27, 1] = "Europium(III) oxide";
            OxidesName[28, 0] = "Gd2O3";
            OxidesName[28, 1] = "Gadolinium(III) oxide";
            OxidesName[29, 0] = "Tb2O3";
            OxidesName[29, 1] = "Terbium(III) oxide";
            OxidesName[30, 0] = "Dy2O3";
            OxidesName[30, 1] = "Dysprosium(III) oxide";
            OxidesName[31, 0] = "Ho2O3";
            OxidesName[31, 1] = "Holmium(III) oxide";
            OxidesName[32, 0] = "Er2O3";
            OxidesName[32, 1] = "Erbium(III) oxide";
            OxidesName[33, 0] = "Tm2O3";
            OxidesName[33, 1] = "Thulium(III) oxide";
            OxidesName[34, 0] = "Yb2O3";
            OxidesName[34, 1] = "Ytterbium(III) oxide";
            OxidesName[35, 0] = "Ta2O5";
            OxidesName[35, 1] = "Tantalum pentoxide";
            OxidesName[36, 0] = "WO3";
            OxidesName[36, 1] = "Tungsten(VI) oxide";
            OxidesName[37, 0] = "Zr02";
            OxidesName[37, 1] = "Zirconium dioxide";
            OxidesName[38, 0] = "Li2O";
            OxidesName[38, 1] = "Lithium oxide";
            OxidesName[39, 0] = "SrO";
            OxidesName[39, 1] = "Strontium oxide";
            OxidesName[40, 0] = "PbO";
            OxidesName[40, 1] = "Lead(II) oxide";
            OxidesName[41, 0] = "ZnO";
            OxidesName[41, 1] = "Zinc oxide";
            OxidesName[42, 0] = "ThO2";
            OxidesName[42, 1] = "Thorium dioxide";
            OxidesName[43, 0] = "U3O8";
            OxidesName[43, 1] = "Triuranium octoxide";
            OxidesName[44, 0] = "Mn3O4";
            OxidesName[44, 1] = "Manganese(II,III) oxide";
            OxidesName[45, 0] = "Mn2O3";
            OxidesName[45, 1] = "Manganese(III) oxide";
            OxidesName[46, 0] = "Sb2O3";
            OxidesName[46, 1] = "Antimony trioxide";
            OxidesName[47, 0] = "SnO2";
            OxidesName[47, 1] = "Tin dioxide";
            OxidesName[48, 0] = "HfO2";
            OxidesName[48, 1] = "Hafnium(IV) oxide";
            OxidesName[49, 0] = "Cu2O";
            OxidesName[49, 1] = "Copper(I) oxide";
            OxidesName[50, 0] = "RuO2";
            OxidesName[50, 1] = "Ruthenium(IV) oxide";
            OxidesName[51, 0] = "Cs2O";
            OxidesName[51, 1] = "Caesium oxide";
            OxidesName[52, 0] = "Rb2O";
            OxidesName[52, 1] = "Rubidium oxide";
            #endregion
        }
    }
}
