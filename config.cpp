class CfgPatches
{
	class bn_csw_load
	{
		units[]={};
		weapons[]={};
		requiredVersion=1.0;
		requiredAddons[]={"A3_Weapons_F", "RDS_StaticWeapons_Core", "AGM_Interaction", "Extended_Eventhandlers"};
	};
};

class Extended_PostInit_EventHandlers
{
	bn_csw_Post_Init_Load = "remoteLoad = compileFinal "" 			private ['_player', '_gun', '_le_mag', '_remember_mags', '_total_ammo','_mag_capacity','_full_mags','_leftovers']; 			_player = _this select 0; 			_gun = _this select 1; 			_le_mag = _this select 2; 			_remember_mags = magazinesAmmoFull (_gun); 			_total_ammo = (_le_mag) select 1; 			{ 				_total_ammo = _total_ammo + (_x select 1); 			} forEach _remember_mags; 			(_gun) removeMagazinesTurret [(_le_mag) select 0, [0]]; 			_mag_capacity = (getNumber (configFile >> 'CfgMagazines' >> (_le_mag) select 0 >> 'count')); 			_full_mags = floor (_total_ammo/_mag_capacity); 			_i = 0; 			for  '_i' from 1 to _full_mags do {(_gun) addMagazineTurret [(_le_mag) select 0,[0]]}; 			_leftovers = _total_ammo % _mag_capacity; 			if (_leftovers>0) then { 				(_gun) addMagazineTurret [(_le_mag) select 0,[0]]; 				(_gun) setAmmo [((weapons (_gun)) select 0), _leftovers]; 			}; 		""; 	";
	
	bn_csw_Post_Init_Unload = " 		remoteUnload = compileFinal "" 			private ['_player', '_gun', '_mags','_holder','_ammo_count','_nearby','_pos']; 			_player = _this select 0; 			_gun = _this select 1; 			_mag = _this select 2; 			_holder = objNull; 			_ammo_count = (_gun) magazineTurretAmmo [(_mag),[0]]; 			_nearby = nearestObjects [_gun, ['GroundWeaponHolder'], 3]; 			if (count _nearby > 0) then {_holder = _nearby select 0}; 			if (isNull _holder) then {_holder = 'GroundWeaponHolder' createVehicle (getPos _gun);}; 			_holder addMagazineAmmoCargo [(_mag), 1, _ammo_count]; 			_pos = ((getPos _gun) vectorAdd ((vectorDir _gun) vectorMultiply -1)); 			_holder setPosATL [_pos select 0, _pos select 1, (getPosATL _gun) select 2]; 			(_gun) removeMagazineTurret [(_mag),[0]]; 			if (!someAmmo _gun) then {_gun removeMagazinesTurret [(weapons _gun select 0),[0]];}; 		""; 	";
	// не хочет жрать код с разбивкой по строкам
	
	
	// "if (isServer) then {'bn_csw_give_owner' addPublicVariableEventHandler {((_this select 1) select 1) setOwner (owner ((_this select 1) select 0))}}";
};

class CfgAmmo {

	class RDS_G_30mm_HE;
	class BN_RDS_G_30mm_HE: RDS_G_30mm_HE {
		airFriction = -0.00049;
	};
	
	/*extern*/ class RHS_ammo_23mm_AA; //B_35mm_AA;
	class RDS_B_23mm_AA: RHS_ammo_23mm_AA {
		indirectHitRange = 1.5;
		visibleFireTime = 4;
	};
};

class CfgMagazines {
	/*extern*/ class Default;

	class CA_Magazine: Default {
	};

	class VehicleMagazine: CA_Magazine {
	};
	
	class RDS_6Rnd_AT13: VehicleMagazine {
	};
	
	class RDS_1Rnd_AT13: RDS_6Rnd_AT13 {
		descriptionShort = "AT13 Metis Missile";
		displayName = "AT13 Metis Missile Container";
		ammo = "RDS_M_AT13_AT";
		count = 1;
		model = "\A3\Weapons_F_beta\Launchers\titan\titan_missile_at";
		picture = "\bn_csw_load\data\equip\m_metis_ca.paa";
		mass = 80;
	};
	
	class RDS_29Rnd_30mm_AGS30: VehicleMagazine {
		scope = 2;
		descriptionShort = "Коробка ВОГ-17";
		displayName = "Коробка ВОГ-17";
		ammo = "BN_RDS_G_30mm_HE";
		count = 29;
		initSpeed = 185;
		maxLeadSpeed = 100;
		nameSound = "grenadelauncher";
		model = "\bn_csw_load\data\models\ace_ags30_mag";
		picture = "\bn_csw_load\data\equip\m_ags30_ca.paa";
		mass = 80;
	};
	
	class RHS_48Rnd_40mm_MK19: VehicleMagazine {
		descriptionShort = "Коробка 40 мм гранат";
		displayName = "Коробка 40 мм гранат";
		nameSound = "grenadelauncher";
		model = "\bn_csw_load\data\models\ace_mk19_mag";
		picture = "\bn_csw_load\data\equip\m_mk19_ca.paa";
		mass = 120;
	};
	
	class rhs_mag_127x108mm_50;
	class BN_50Rnd_127x108: rhs_mag_127x108mm_50 {
		descriptionShort = "Коробка 12,7x108 мм 50 шт.";
		displayName = "Коробка 12,7x108 мм";
		model = "\bn_csw_load\data\models\ace_kord_mag";
		picture = "\rhsafrf\addons\rhs_weapons\icons\pkpbox_ca.paa";
		mass = 80;
	};
	
	class rhs_mag_100rnd_127x99_mag;
	class BN_100Rnd_127x99: rhs_mag_100rnd_127x99_mag {
		descriptionShort = "Коробка .50, 100 шт.";
		displayName = "Коробка .50";
		model = "\bn_csw_load\data\models\ace_m2_mag";
		picture = "\bn_csw_load\data\equip\m_m2_ca.paa";
		mass = 120;
	};
	
	class RDS_PG9_AT;
	class BN_PG9_AT: RDS_PG9_AT {
		descriptionShort = "ПГ-9, выстрел СПГ кумулятивный";
		displayName = "ПГ-9";
		model = "\rhsafrf\addons\rhs_weapons\rpg7\magazines\rhs_pg7vl_mag";
		picture = "\bn_csw_load\data\equip\m_pg9_ca.paa";
		mass = 50;
	};

	class RDS_OG9_HE;
	class BN_OG9_HE: RDS_OG9_HE	{
		descriptionShort = "ОГ-9, выстрел СПГ осколочный";
		displayName = "ОГ-9";
		model = "\rhsafrf\addons\rhs_weapons\rpg7\magazines\rhs_og7v_mag";
		picture = "\bn_csw_load\data\equip\m_og9_ca.paa";
		mass = 60;
	};
	
	class RDS_2000Rnd_23mm_AZP85;
	class RDS_40Rnd_23mm_AZP85: RDS_2000Rnd_23mm_AZP85 {
		descriptionShort = "Коробка с лентой ОФЗТ";
		displayName = "Коробка с лентой к ЗУ";
		model = "\bn_csw_load\data\models\ace_kord_mag";
		picture = "\rhsafrf\addons\rhs_weapons\icons\pkpbox_ca.paa";
		mass = 160;
		count = 100;
		tracersEvery = 1;
	};
};

class CfgWeapons {
	class RDS_AT13LauncherSingle;
	class BN_RDS_AT13LauncherSingle: RDS_AT13LauncherSingle {
		magazineReloadTime = 0;
		bn_csw_ReloadTime = 15;
		bn_csw_extra_capacity = 0;
		magazines[] = {"RDS_1Rnd_AT13"};
		canlock = 0;
		AGM_Backblast_Angle = 60;
		AGM_Backblast_Range = 10;
		AGM_Backblast_Damage = 0.7;
	};
	
	class RDS_AGS30;
	class BN_RDS_AGS30:	RDS_AGS30 {
		magazineReloadTime = 0;
		bn_csw_extra_capacity = 1;
		bn_csw_ReloadTime = 12;
	};

	class RHS_MK19;
	class BN_RHS_MK19: RHS_MK19  {
		magazineReloadTime = 0;
		bn_csw_extra_capacity = 1;
		bn_csw_ReloadTime = 12;
	};
	
	class RHS_M2;
	class BN_RHS_M2: RHS_M2  {
		magazines[] = {"BN_100Rnd_127x99"};
		magazineReloadTime = 0;
		bn_csw_extra_capacity = 1;
		bn_csw_ReloadTime = 7;
	};
	
	class rhs_weap_nsvt;
	class BN_rhs_weap_nsvt: rhs_weap_nsvt  {
		magazines[] = {"BN_50Rnd_127x108"};
		magazineReloadTime = 0;
		bn_csw_extra_capacity = 2;
		bn_csw_ReloadTime = 7;
	}; 
	
	class RDS_KORD;
	class BN_RDS_KORD: RDS_KORD	{
		displayName = "12,7 мм пулемет";
		descriptionShort = "12,7 мм пулемет";
		magazines[] = {"BN_50Rnd_127x108"};
		magazineReloadTime = 0;
		bn_csw_extra_capacity = 2;
		bn_csw_ReloadTime = 7;
	};
	
	/*extern*/ class RocketPods;

	class RDS_SPG9;
	class BN_SPG9: RDS_SPG9 {
		magazines[] = {"BN_PG9_AT", "BN_OG9_HE"};
		magazineReloadTime = 0;
		bn_csw_extra_capacity = 0;
		bn_csw_ReloadTime = 12;
		AGM_Backblast_Angle = 60;
		AGM_Backblast_Range = 10;
		AGM_Backblast_Damage = 0.7;
	};
	
	class RDS_Igla_twice;
	class BN_Dzhigit: RDS_Igla_twice {
		displayName = "Игла";
		magazineReloadTime = 0;
		bn_csw_extra_capacity = 1;
		bn_csw_ReloadTime = 15;
		magazines[] = {"rhs_mag_9k38_rocket"};
	};
	
	class RDS_2A14;
	class BN_ZU23: RDS_2A14 {
		magazineReloadTime = 0;
		bn_csw_ReloadTime = 30;
		bn_csw_extra_capacity = 2;
	};
};

class CfgVehicles {
	/*extern*/ class LandVehicle;
	
	class StaticWeapon: LandVehicle {
		class AGM_Actions;
		class BN_CSW_Actions: AGM_Actions {
			class BN_CSW_Load {
				displayName = "Зарядить";
				distance = 2;
				condition = "true";
				icon = "\AGM_Interaction\UI\team\team_green_ca.paa";
				statement = "0 = [_target, _player] execVM '\bn_csw_load\scripts\bn_csw_load.sqf';";
				showDisabled = 1;
				priority = 5;
				hotkey = "L";
				enableInside = 0;
			};
			class BN_CSW_Unload {
				displayName = "Разрядить";
				distance = 2;
				condition = "true";
				icon = "\AGM_Interaction\UI\team\team_red_ca.paa";
				statement = "0 = [_target, _player] execVM '\bn_csw_load\scripts\bn_csw_unload.sqf';";
				showDisabled = 1;
				priority = 5;
				hotkey = "U";
				enableInside = 0;
			};
		};		
	};

	class StaticATWeapon: StaticWeapon {
		/*extern*/ class Turrets;
		/*extern*/ class MainTurret;
	};
	
	class StaticGrenadeLauncher: StaticWeapon {
		/*extern*/ class Turrets;
		/*extern*/ class MainTurret;
		/*extern*/ class ViewOptics;
	};
	
	class StaticMGWeapon: StaticWeapon {
		/*extern*/ class Turrets;
		/*extern*/ class MainTurret;
	};

	class RDS_Metis_Base: StaticATWeapon {
		/*extern*/ class Turrets;
		/*extern*/ class MainTurret;
		class AGM_Actions: AGM_Actions {
			class BN_CSW_Load {
				displayName = "Зарядить";
				distance = 2;
				condition = "true";
				icon = "\AGM_Interaction\UI\team\team_green_ca.paa";
				statement = "0 = [_target, _player] execVM '\bn_csw_load\scripts\bn_csw_load.sqf';";
				showDisabled = 1;
				priority = 1;
				hotkey = "L";
				enableInside = 0;
			};
			class BN_CSW_Unload {
				displayName = "Разрядить";
				distance = 2;
				condition = "true";
				icon = "\AGM_Interaction\UI\team\team_red_ca.paa";
				statement = "0 = [_target, _player] execVM '\bn_csw_load\scripts\bn_csw_unload.sqf';";
				showDisabled = 1;
				priority = 1;
				hotkey = "U";
				enableInside = 0;
			};
		};
	};
	class StaticCannon: StaticWeapon {
		/*extern*/ class ViewOptics;
		/*extern*/ class Turrets;
		/*extern*/ class MainTurret;
	};
	
	class RDS_ZU23_base: StaticCannon {
	
		class AGM_Actions: AGM_Actions {
			class BN_CSW_Load {
				displayName = "Зарядить";
				distance = 2;
				condition = "true";
				icon = "\AGM_Interaction\UI\team\team_green_ca.paa";
				statement = "0 = [_target, _player] execVM '\bn_csw_load\scripts\bn_csw_load.sqf';";
				showDisabled = 1;
				priority = 1;
				hotkey = "L";
				enableInside = 0;
			};
			class BN_CSW_Unload {
				displayName = "Разрядить";
				distance = 2;
				condition = "true";
				icon = "\AGM_Interaction\UI\team\team_red_ca.paa";
				statement = "0 = [_target, _player] execVM '\bn_csw_load\scripts\bn_csw_unload.sqf';";
				showDisabled = 1;
				priority = 1;
				hotkey = "U";
				enableInside = 0;
			};
		};
		
		class Turrets: Turrets {

			class MainTurret: MainTurret {
				minTurn = -180;
				maxTurn = 180;
				initTurn = 0;
				minElev = -10;
				maxElev = 85;
				initElev = 0;
				weapons[] = {"BN_ZU23"};
				magazines[] = {"RDS_40Rnd_23mm_AZP85"};
				gunnerAction = "Hilux_Cargo01";
				selectionFireAnim = "zasleh";
				gunnerOpticsModel = "\RDS_StaticW\zu23\2Dscope_RUAA5";
				gunnerOpticsEffect[] = {"OpticsCHAbera1", "OpticsBlur2"};
				gunnerForceOptics = 0;
				memoryPointsGetInGunner = "pos_gunner_dir";
				memoryPointsGetInGunnerDir = "pos_gunner";

				class ViewGunner {
					initAngleX = 5;
					minAngleX = -30;
					maxAngleX = 30;
					initAngleY = 0;
					minAngleY = -100;
					maxAngleY = 100;
					initFov = 0.700000;
					minFov = 0.250000;
					maxFov = 1.100000;
				};

				class ViewOptics {
					initAngleX = 0;
					minAngleX = -30;
					maxAngleX = 30;
					initAngleY = 0;
					minAngleY = -100;
					maxAngleY = 100;
					initFov = 0.093000;
					minFov = 0.093000;
					maxFov = 0.093000;
				};
			};
		};

 		class AnimationSources {

			class muzzle_source {
				source = "reload";
				weapon = "BN_ZU23";
			};

			class fire_anim {
				source = "revolving";
				weapon = "BN_ZU23";
			};
		}; 
	};

	class RDS_ZU23_AAF: RDS_ZU23_base {
		class Turrets: Turrets {
			class MainTurret: MainTurret {
				minTurn = -180;
				maxTurn = 180;
				initTurn = 0;
				minElev = -10;
				maxElev = 85;
				initElev = 0;
				weapons[] = {"BN_ZU23"};
				magazines[] = {"RDS_40Rnd_23mm_AZP85"};
				gunnerAction = "Hilux_Cargo01";
				selectionFireAnim = "zasleh";
				gunnerOpticsModel = "\RDS_StaticW\zu23\2Dscope_RUAA5";
				gunnerOpticsEffect[] = {"OpticsCHAbera1", "OpticsBlur2"};
				gunnerForceOptics = 0;
				memoryPointsGetInGunner = "pos_gunner_dir";
				memoryPointsGetInGunnerDir = "pos_gunner";

				class ViewGunner {
					initAngleX = 5;
					minAngleX = -30;
					maxAngleX = 30;
					initAngleY = 0;
					minAngleY = -100;
					maxAngleY = 100;
					initFov = 0.700000;
					minFov = 0.250000;
					maxFov = 1.100000;
				};

				class ViewOptics {
					initAngleX = 0;
					minAngleX = -30;
					maxAngleX = 30;
					initAngleY = 0;
					minAngleY = -100;
					maxAngleY = 100;
					initFov = 0.093000;
					minFov = 0.093000;
					maxFov = 0.093000;
				};
			};
		};

	};
	
	class StaticAAWeapon: StaticWeapon {
		/*extern*/ class Turrets;
		/*extern*/ class MainTurret;
	};
	
	class RDS_Igla_AA_pod_Base: StaticAAWeapon {
		gunnercansee = "2+4+8+32";
		displayName = "$STR_DN_IGLA_AA_POD_EAST";
		mapsize = 2.800000;
		model = "RDS_StaticW\igla\igla_AA_pod";
		icon = "RDS_StaticW\data\map_ico\icomap_igla_aa_pod_CA.paa";
		picture = "\RDS_StaticW\data\ico\igla_aa_pod_ca.paa";
		UiPicture = "\RDS_StaticW\data\ico\igla_aa_pod_ca.paa";
		
		class AGM_Actions: AGM_Actions {
			class BN_CSW_Load {
				displayName = "Зарядить";
				distance = 2;
				condition = "true";
				icon = "\AGM_Interaction\UI\team\team_green_ca.paa";
				statement = "0 = [_target, _player] execVM '\bn_csw_load\scripts\bn_csw_load.sqf';";
				showDisabled = 1;
				priority = 1;
				hotkey = "L";
				enableInside = 0;
			};
			class BN_CSW_Unload {
				displayName = "Разрядить";
				distance = 2;
				condition = "true";
				icon = "\AGM_Interaction\UI\team\team_red_ca.paa";
				statement = "0 = [_target, _player] execVM '\bn_csw_load\scripts\bn_csw_unload.sqf';";
				showDisabled = 1;
				priority = 1;
				hotkey = "U";
				enableInside = 0;
			};
		};
		/*extern*/ class Turrets;
		/*extern*/ class MainTurret;
	};
	
	class RDS_Igla_AA_pod_AAF: RDS_Igla_AA_pod_Base {
		class Turrets: Turrets {
			class MainTurret: MainTurret {
				minTurn = -180;
				maxTurn = 180;
				gunneraction = "Mi17_Cargo02";
				gunneropticseffect[] = {"OpticsCHAbera1", "OpticsBlur2"};
				gunneropticsmodel = "\RDS_StaticW\optika_TOW";
				magazines[] = {"rhs_mag_9k38_rocket", "rhs_mag_9k38_rocket"};
				maxelev = 120;
				memorypointsgetingunner = "pos_gunner";
				memorypointsgetingunnerdir = "pos_gunner_dir";
				minelev = -10;
				weapons[] = {"BN_Dzhigit"};

				class ViewOptics {
					initanglex = 0;
					initangley = 0;
					initfov = 0.155000;
					maxanglex = 30;
					maxangley = 100;
					maxfov = 0.155000;
					minanglex = -30;
					minangley = -100;
					minfov = 0.047000;
				};
			};
		};
	};
	
	class RDS_Metis_AAF: RDS_Metis_Base {
		class Turrets: Turrets {
			class MainTurret: MainTurret {
				weapons[] = {"BN_RDS_AT13LauncherSingle"};
				magazines[] = {"RDS_1Rnd_AT13"};
				// copied
				gunnerAction = "Metis_Gunner";
				gunnerOpticsModel = "\RDS_StaticW\2Dscope_Metis";
				gunnerOpticsEffect[] = {"OpticsCHAbera1", "OpticsBlur2"};
				memoryPointsGetInGunner = "pos_gunner_dir";
				memoryPointsGetInGunnerDir = "pos_gunner";
				minTurn = -45;
				maxTurn = 45;
				initTurn = 0;
				minElev = -10;
				maxElev = 40;
				initElev = 0;
				ejectDeadGunner = 0;
				gunnerForceOptics = 0;

				class ViewGunner {
					initAngleX = 5;
					minAngleX = -30;
					maxAngleX = 30;
					initAngleY = 0;
					minAngleY = -100;
					maxAngleY = 100;
					initFov = 0.700000;
					minFov = 0.250000;
					maxFov = 1.100000;
				};

				class ViewOptics {
					initAngleX = 0;
					minAngleX = -30;
					maxAngleX = 30;
					initAngleY = 0;
					minAngleY = -100;
					maxAngleY = 100;
					initFov = 0.078000;
					minFov = 0.078000;
					maxFov = 0.078000;
					visionMode[] = {"Normal", "TI"};
					thermalMode[] = {4, 5};
				};
			};
		};
	};
	
	class RDS_AGS_base: StaticGrenadeLauncher {
	};
	
	class RDS_AGS_AAF: RDS_AGS_base {
	
		class AGM_Actions: AGM_Actions {
			class BN_CSW_Load {
				displayName = "Зарядить";
				distance = 2;
				condition = "true";
				icon = "\AGM_Interaction\UI\team\team_green_ca.paa";
				statement = "0 = [_target, _player] execVM '\bn_csw_load\scripts\bn_csw_load.sqf';";
				showDisabled = 1;
				priority = 1;
				hotkey = "L";
				enableInside = 0;
			};
			class BN_CSW_Unload {
				displayName = "Разрядить";
				distance = 2;
				condition = "true";
				icon = "\AGM_Interaction\UI\team\team_red_ca.paa";
				statement = "0 = [_target, _player] execVM '\bn_csw_load\scripts\bn_csw_unload.sqf';";
				showDisabled = 1;
				priority = 1;
				hotkey = "U";
				enableInside = 0;
			};
		};
		
		class AnimationSources {
			class muzzle_source {
				source = "reload";
				weapon = "BN_RDS_AGS30";
			};

			class fire_anim {
				source = "revolving";
				weapon = "BN_RDS_AGS30";
			};
		}; 
	
		class Turrets: Turrets {
			class MainTurret: MainTurret {
				minElev = -10;
				maxelev = 70;
				minTurn = -90;
				maxTurn = 90;
				initTurn = 0;
				weapons[] = {"BN_RDS_AGS30"};
				magazines[] = {"RDS_29Rnd_30mm_AGS30"};
				gunnerAction = "AGS_Gunner";
				gunnerOpticsModel = "\RDS_StaticW\optika_AGS30";
				gunnerOpticsEffect[] = {"OpticsCHAbera1", "OpticsBlur2"};
				gunnerForceOptics = 0;
				memoryPointsGetInGunner = "pos_gunner_dir";
				memoryPointsGetInGunnerDir = "pos_gunner";

				class ViewGunner {
					initAngleX = 5;
					minAngleX = -30;
					maxAngleX = 30;
					initAngleY = 0;
					minAngleY = -100;
					maxAngleY = 100;
					initFov = 0.700000;
					minFov = 0.250000;
					maxFov = 1.100000;
				};

				class ViewOptics:ViewOptics {
					initFov = 0.196000;
					minFov = 0.196000;
					maxFov = 0.196000;
				};
			};
		};
	};
	
 	class RHS_MK19_TriPod_base: StaticGrenadeLauncher {
		class AGM_Actions: AGM_Actions {
			class BN_CSW_Load {
				displayName = "Зарядить";
				distance = 2;
				condition = "true";
				icon = "\AGM_Interaction\UI\team\team_green_ca.paa";
				statement = "0 = [_target, _player] execVM '\bn_csw_load\scripts\bn_csw_load.sqf';";
				showDisabled = 1;
				priority = 1;
				hotkey = "L";
				enableInside = 0;
			};
			class BN_CSW_Unload {
				displayName = "Разрядить";
				distance = 2;
				condition = "true";
				icon = "\AGM_Interaction\UI\team\team_red_ca.paa";
				statement = "0 = [_target, _player] execVM '\bn_csw_load\scripts\bn_csw_unload.sqf';";
				showDisabled = 1;
				priority = 1;
				hotkey = "U";
				enableInside = 0;
			};
		};
		
		class AnimationSources {
			class muzzle_source {
				source = "reload";
				weapon = "BN_RHS_MK19";
			};

			class fire_anim {
				source = "revolving";
				weapon = "BN_RHS_MK19";
			};
			
			class belt_rotation {
				weapon = "BN_RHS_MK19";
			};
			class ReloadMagazine {
				weapon = "BN_RHS_MK19";
			};
			class Revolving {
				weapon = "BN_RHS_MK19";
			};
		}; 
		
		class Turrets: Turrets {

			class MainTurret: MainTurret {
				gunnerLeftHandAnimName = "otochlaven";
				gunnerRightHandAnimName = "otochlaven";
				gunnerOpticsModel = "\A3\weapons_f\reticle\optics_empty";
				minElev = -10;
				minTurn = -90;
				maxTurn = 90;
				initTurn = 0;
				weapons[] = {"BN_RHS_MK19"};
				magazines[] = {"RHS_48Rnd_40mm_MK19"};
				gunnerAction = "LowTripod_Gunner";
			};
		};
	}; 
	
	class RHS_MK19_TriPod_D: RHS_MK19_TriPod_base {
		class Turrets: Turrets {

			class MainTurret: MainTurret {
				gunnerLeftHandAnimName = "otochlaven";
				gunnerRightHandAnimName = "otochlaven";
				gunnerOpticsModel = "\A3\weapons_f\reticle\optics_empty";
				discreteDistance[] = {300, 400, 500, 600, 700, 750, 800, 850, 900, 950, 1000, 1050, 1100, 1150, 1200, 1250, 1300, 1450, 1400, 1450, 1500};
				discreteDistanceInitIndex = 0;
				minElev = -10;
				minTurn = -90;
				maxTurn = 90;
				initTurn = 0;
				weapons[] = {"BN_RHS_MK19"};
				magazines[] = {"RHS_48Rnd_40mm_MK19"};
				gunnerAction = "LowTripod_Gunner";
			};
		};
	};
	
	class RHS_MK19_TriPod_WD: RHS_MK19_TriPod_base {
		class Turrets: Turrets {

			class MainTurret: MainTurret {
				gunnerLeftHandAnimName = "otochlaven";
				gunnerRightHandAnimName = "otochlaven";
				gunnerOpticsModel = "\A3\weapons_f\reticle\optics_empty";
				discreteDistance[] = {300, 400, 500, 600, 700, 750, 800, 850, 900, 950, 1000, 1050, 1100, 1150, 1200, 1250, 1300, 1450, 1400, 1450, 1500};
				discreteDistanceInitIndex = 0;
				minElev = -10;
				minTurn = -90;
				maxTurn = 90;
				initTurn = 0;
				weapons[] = {"BN_RHS_MK19"};
				magazines[] = {"RHS_48Rnd_40mm_MK19"};
				gunnerAction = "LowTripod_Gunner";
			};
		};
	};
	
 	class RHS_NSV_TriPod_base: StaticMGWeapon {
		class AGM_Actions: AGM_Actions {
			class BN_CSW_Load {
				displayName = "Зарядить";
				distance = 2;
				condition = "true";
				icon = "\AGM_Interaction\UI\team\team_green_ca.paa";
				statement = "0 = [_target, _player] execVM '\bn_csw_load\scripts\bn_csw_load.sqf';";
				showDisabled = 1;
				priority = 1;
				hotkey = "L";
				enableInside = 0;
			};
			class BN_CSW_Unload {
				displayName = "Разрядить";
				distance = 2;
				condition = "true";
				icon = "\AGM_Interaction\UI\team\team_red_ca.paa";
				statement = "0 = [_target, _player] execVM '\bn_csw_load\scripts\bn_csw_unload.sqf';";
				showDisabled = 1;
				priority = 1;
				hotkey = "U";
				enableInside = 0;
			};
		};
		class Turrets: Turrets {

			class MainTurret: MainTurret {
				gunnerLeftHandAnimName = "otochlaven_shake";
				gunnerRightHandAnimName = "otochlaven_shake";
				minElev = -20;
				maxelev = 15;
				weapons[] = {"BN_RDS_KORD"};
				magazines[] = {"BN_50Rnd_127x108"};
				gunnerAction = "LowKORD_Gunner";
				minTurn = -60;
				maxTurn = 60;
				initTurn = 0;
				optics = 1;
				turretInfoType = "RscWeaponZeroing";
				discreteDistance[] = {100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500};
				discreteDistanceInitIndex = 2;
				selectionFireAnim = "zasleh";
				gunnerOpticsModel = "\A3\weapons_f\reticle\optics_empty";

				class ViewOptics {
					initAngleX = 0;
					minAngleX = -30;
					maxAngleX = 30;
					initAngleY = 0;
					minAngleY = -100;
					maxAngleY = 100;
					initFov = 0.700000;
					minFov = 0.250000;
					maxFov = 1.100000;
				};
			};
		};
		
		class AnimationSources {
			class muzzleHMG_ROT {
				weapon = "BN_RDS_KORD";
			};
			class ReloadAnim {
				weapon = "BN_RDS_KORD";
			};
/* 			class ReloadMagazine {
				weapon = "BN_RDS_KORD";
			}; */
			class Revolving {
				weapon = "BN_RDS_KORD";
			};
		}; 
		
	}; 
	class RHS_NSV_TriPod_MSV: RHS_NSV_TriPod_base {
		class Turrets: Turrets {

			class MainTurret: MainTurret {
				gunnerLeftHandAnimName = "otochlaven_shake";
				gunnerRightHandAnimName = "otochlaven_shake";
				minElev = -20;
				maxelev = 15;
				weapons[] = {"BN_RDS_KORD"};
				magazines[] = {"BN_50Rnd_127x108"};
				gunnerAction = "LowKORD_Gunner";
				minTurn = -60;
				maxTurn = 60;
				initTurn = 0;
				optics = 1;
				turretInfoType = "RscWeaponZeroing";
				discreteDistance[] = {100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500};
				discreteDistanceInitIndex = 2;
				selectionFireAnim = "zasleh";
				gunnerOpticsModel = "\A3\weapons_f\reticle\optics_empty";

				class ViewOptics {
					initAngleX = 0;
					minAngleX = -30;
					maxAngleX = 30;
					initAngleY = 0;
					minAngleY = -100;
					maxAngleY = 100;
					initFov = 0.700000;
					minFov = 0.250000;
					maxFov = 1.100000;
				};
			};
		};
	}; 
	
	class RHS_NSV_TriPod_VDV: RHS_NSV_TriPod_base {
		class Turrets: Turrets {

			class MainTurret: MainTurret {
				gunnerLeftHandAnimName = "otochlaven_shake";
				gunnerRightHandAnimName = "otochlaven_shake";
				minElev = -20;
				maxelev = 15;
				weapons[] = {"BN_RDS_KORD"};
				magazines[] = {"BN_50Rnd_127x108"};
				gunnerAction = "LowKORD_Gunner";
				minTurn = -60;
				maxTurn = 60;
				initTurn = 0;
				optics = 1;
				turretInfoType = "RscWeaponZeroing";
				discreteDistance[] = {100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500};
				discreteDistanceInitIndex = 2;
				selectionFireAnim = "zasleh";
				gunnerOpticsModel = "\A3\weapons_f\reticle\optics_empty";

				class ViewOptics {
					initAngleX = 0;
					minAngleX = -30;
					maxAngleX = 30;
					initAngleY = 0;
					minAngleY = -100;
					maxAngleY = 100;
					initFov = 0.700000;
					minFov = 0.250000;
					maxFov = 1.100000;
				};
			};
		};
	}; 
	
	class RDS_KORD_Base: StaticMGWeapon {
		class Turrets: Turrets {

			class MainTurret: MainTurret {
				gunnerLeftHandAnimName = "otochlaven_shake";
				gunnerRightHandAnimName = "otochlaven_shake";
				minElev = -20;
				maxelev = 15;
				weapons[] = {"BN_RDS_KORD"};
				magazines[] = {"BN_50Rnd_127x108"};
				gunnerAction = "LowKORD_Gunner";
				minTurn = -60;
				maxTurn = 60;
				initTurn = 0;
				optics = 1;
				turretInfoType = "RscWeaponZeroing";
				discreteDistance[] = {100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500};
				discreteDistanceInitIndex = 2;
				selectionFireAnim = "zasleh";
				gunnerOpticsModel = "\A3\weapons_f\reticle\optics_empty";

				class ViewOptics {
					initAngleX = 0;
					minAngleX = -30;
					maxAngleX = 30;
					initAngleY = 0;
					minAngleY = -100;
					maxAngleY = 100;
					initFov = 0.700000;
					minFov = 0.250000;
					maxFov = 1.100000;
				};
			};
		};
	}; 
	class RDS_KORD_AAF: RDS_KORD_Base {

		class Turrets: Turrets {

			class MainTurret: MainTurret {
				gunnerLeftHandAnimName = "otochlaven_shake";
				gunnerRightHandAnimName = "otochlaven_shake";
				minElev = -20;
				maxelev = 15;
				weapons[] = {"BN_RDS_KORD"};
				magazines[] = {"BN_50Rnd_127x108"};
				gunnerAction = "LowKORD_Gunner";
				minTurn = -60;
				maxTurn = 60;
				initTurn = 0;
				optics = 1;
				turretInfoType = "RscWeaponZeroing";
				discreteDistance[] = {100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500};
				discreteDistanceInitIndex = 2;
				selectionFireAnim = "zasleh";
				gunnerOpticsModel = "\A3\weapons_f\reticle\optics_empty";

				class ViewOptics {
					initAngleX = 0;
					minAngleX = -30;
					maxAngleX = 30;
					initAngleY = 0;
					minAngleY = -100;
					maxAngleY = 100;
					initFov = 0.700000;
					minFov = 0.250000;
					maxFov = 1.100000;
				};
			};
		};
/* 
		class AnimationSources {

			class ReloadAnim {
				source = "reload";
				weapon = "RDS_KORD";
			};

			class ReloadMagazine {
				source = "reloadmagazine";
				weapon = "RDS_KORD";
			};

			class Revolving {
				source = "revolving";
				weapon = "RDS_KORD";
			};
		};
		armorStructural = 10;

		class Library {
			libTextDesc = "$STR_LIB_KORD";
		}; */
	};

	class RDS_KORD_high_AAF: RDS_KORD_Base {
		scope = 2;
		side = 2;
		faction = "IND_F";
		crew = "I_Soldier_F";
		typicalCargo[] = {"I_Soldier_F"};
		displayName = "$STR_DN_KORD";
		model = "\RDS_StaticW\KORD\KORD_6u16sp";
		icon = "RDS_StaticW\data\map_ico\icomap_kord6u16sp_CA.paa";
		picture = "\RDS_StaticW\data\ico\kord6u16sp_ca.paa";
		UiPicture = "\RDS_StaticW\data\ico\kord6u16sp_ca.paa";

		class Turrets: Turrets {

			class MainTurret: MainTurret {
				minElev = -7;
				maxelev = 45;
				weapons[] = {"BN_RDS_KORD"};
				magazines[] = {"BN_50Rnd_127x108"};
				gunnerAction = "KORD_Gunner";
				minTurn = -180;
				maxTurn = 180;
				initTurn = 0;
			};
		};
	};
	
	class  RDS_SPG9_base: StaticATWeapon {
		class AGM_Actions: AGM_Actions {
			class BN_CSW_Load {
				displayName = "Зарядить";
				distance = 2;
				condition = "true";
				icon = "\AGM_Interaction\UI\team\team_green_ca.paa";
				statement = "0 = [_target, _player] execVM '\bn_csw_load\scripts\bn_csw_load.sqf';";
				showDisabled = 1;
				priority = 1;
				hotkey = "L";
				enableInside = 0;
			};
			class BN_CSW_Unload {
				displayName = "Разрядить";
				distance = 2;
				condition = "true";
				icon = "\AGM_Interaction\UI\team\team_red_ca.paa";
				statement = "0 = [_target, _player] execVM '\bn_csw_load\scripts\bn_csw_unload.sqf';";
				showDisabled = 1;
				priority = 1;
				hotkey = "U";
				enableInside = 0;
			};
		};
		
		class AnimationSources {

			class ReloadAnim {
				source = "reload";
				weapon = "BN_SPG9";
			};
		};
		
		class Turrets: Turrets {
			class MainTurret: MainTurret {
				weapons[] = {"BN_SPG9"};
				magazines[] = {"BN_PG9_AT"};
				gunnerAction = "SPG_Gunner";
				gunnerOpticsModel = "\RDS_StaticW\2Dscope_SPG_4";
				gunnerOpticsEffect[] = {"OpticsCHAbera1", "OpticsBlur2", "TankGunnerOptics1"};
				memoryPointsGetInGunner = "pos_gunner_dir";
				memoryPointsGetInGunnerDir = "pos_gunner";
				minTurn = -45;
				maxTurn = 45;
				initTurn = 0;
				minElev = -10;
				maxElev = 40;
				initElev = 0;
				ejectDeadGunner = 0;
				gunnerForceOptics = 0;

				class ViewGunner {
					initAngleX = 5;
					minAngleX = -30;
					maxAngleX = 30;
					initAngleY = 0;
					minAngleY = -100;
					maxAngleY = 100;
					initFov = 0.700000;
					minFov = 0.250000;
					maxFov = 1.100000;
				};

				class ViewOptics {
					initAngleX = 0;
					minAngleX = -30;
					maxAngleX = 30;
					initAngleY = 0;
					minAngleY = -100;
					maxAngleY = 100;
					initFov = 0.111000;
					minFov = 0.111000;
					maxFov = 0.111000;
				};
			};
		};
	
	};
	class RDS_SPG9_AAF: RDS_SPG9_base {
		class AnimationSources;
		class Turrets: Turrets {
			class MainTurret: MainTurret {
				weapons[] = {"BN_SPG9"};
				magazines[] = {"BN_PG9_AT"};
				gunnerAction = "SPG_Gunner";
				gunnerOpticsModel = "\RDS_StaticW\2Dscope_SPG_4";
				gunnerOpticsEffect[] = {"OpticsCHAbera1", "OpticsBlur2", "TankGunnerOptics1"};
				memoryPointsGetInGunner = "pos_gunner_dir";
				memoryPointsGetInGunnerDir = "pos_gunner";
				minTurn = -45;
				maxTurn = 45;
				initTurn = 0;
				minElev = -10;
				maxElev = 40;
				initElev = 0;
				ejectDeadGunner = 0;
				gunnerForceOptics = 0;

				class ViewGunner {
					initAngleX = 5;
					minAngleX = -30;
					maxAngleX = 30;
					initAngleY = 0;
					minAngleY = -100;
					maxAngleY = 100;
					initFov = 0.700000;
					minFov = 0.250000;
					maxFov = 1.100000;
				};

				class ViewOptics {
					initAngleX = 0;
					minAngleX = -30;
					maxAngleX = 30;
					initAngleY = 0;
					minAngleY = -100;
					maxAngleY = 100;
					initFov = 0.111000;
					minFov = 0.111000;
					maxFov = 0.111000;
				};
			};
		};
	};
	
	class rhs_m2staticmg_base: StaticMGWeapon {
		class AGM_Actions: AGM_Actions {
			class BN_CSW_Load {
				displayName = "Зарядить";
				distance = 2;
				condition = "true";
				icon = "\AGM_Interaction\UI\team\team_green_ca.paa";
				statement = "0 = [_target, _player] execVM '\bn_csw_load\scripts\bn_csw_load.sqf';";
				showDisabled = 1;
				priority = 1;
				hotkey = "L";
				enableInside = 0;
			};
			class BN_CSW_Unload {
				displayName = "Разрядить";
				distance = 2;
				condition = "true";
				icon = "\AGM_Interaction\UI\team\team_red_ca.paa";
				statement = "0 = [_target, _player] execVM '\bn_csw_load\scripts\bn_csw_unload.sqf';";
				showDisabled = 1;
				priority = 1;
				hotkey = "U";
				enableInside = 0;
			};
		};
		
		class Turrets: Turrets {
			class MainTurret: MainTurret {
				optics = 1;
				turretInfoType = "RscWeaponZeroing";
				discreteDistance[] = {100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500, 1600, 1700, 1800, 1900, 2000, 2100, 2200, 2300};
				discreteDistanceInitIndex = 2;
				gunnerOpticsModel = "\A3\weapons_f\reticle\optics_empty";
				gunnerLeftHandAnimName = "otochlaven_shake";
				gunnerRightHandAnimName = "otochlaven_shake";
				selectionFireAnim = "zasleh";
				minElev = -20;
				minTurn = -180;
				maxTurn = 180;
				weapons[] = {"BN_RHS_M2"};
				magazines[] = {"BN_100Rnd_127x99"};
				gunnerAction = "M2_Gunner";
			};
		};
	};
	class RHS_M2StaticMG_D: rhs_m2staticmg_base {
		class Turrets: Turrets {
			class MainTurret: MainTurret {
				optics = 1;
				turretInfoType = "RscWeaponZeroing";
				discreteDistance[] = {100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500, 1600, 1700, 1800, 1900, 2000, 2100, 2200, 2300};
				discreteDistanceInitIndex = 2;
				gunnerOpticsModel = "\A3\weapons_f\reticle\optics_empty";
				gunnerLeftHandAnimName = "otochlaven_shake";
				gunnerRightHandAnimName = "otochlaven_shake";
				selectionFireAnim = "zasleh";
				minElev = -20;
				minTurn = -180;
				maxTurn = 180;
				weapons[] = {"BN_RHS_M2"};
				magazines[] = {"BN_100Rnd_127x99"};
				gunnerAction = "M2_Gunner";
			};
		};
		
		class AnimationSources {
			class muzzleHMG_ROT {
				source = "ammorandom";
				weapon = "BN_RHS_M2";
			};
			class ReloadAnim {
				source = "reload";
				weapon = "BN_RHS_M2";
			};
 			class ReloadMagazine {
				source = "reloadmagazine";
				weapon = "BN_RHS_M2";
			}; 
			class Revolving {
				source = "revolving";
				weapon = "BN_RHS_M2";
			};
		}; 
	};
	
	class RHS_M2StaticMG_WD: rhs_m2staticmg_base {
		class Turrets: Turrets {
			class MainTurret: MainTurret {
				optics = 1;
				turretInfoType = "RscWeaponZeroing";
				discreteDistance[] = {100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500, 1600, 1700, 1800, 1900, 2000, 2100, 2200, 2300};
				discreteDistanceInitIndex = 2;
				gunnerOpticsModel = "\A3\weapons_f\reticle\optics_empty";
				gunnerLeftHandAnimName = "otochlaven_shake";
				gunnerRightHandAnimName = "otochlaven_shake";
				selectionFireAnim = "zasleh";
				minElev = -20;
				minTurn = -180;
				maxTurn = 180;
				weapons[] = {"BN_RHS_M2"};
				magazines[] = {"BN_100Rnd_127x99"};
				gunnerAction = "M2_Gunner";
			};
		};
	};
	
	class RHS_M2StaticMG_MiniTripod_base: rhs_m2staticmg_base {
		class Turrets: Turrets {
			class MainTurret: MainTurret {
				optics = 1;
				turretInfoType = "RscWeaponZeroing";
				discreteDistance[] = {100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500, 1600, 1700, 1800, 1900, 2000, 2100, 2200, 2300};
				discreteDistanceInitIndex = 2;
				gunnerOpticsModel = "\A3\weapons_f\reticle\optics_empty";
				gunnerLeftHandAnimName = "otochlaven_shake";
				gunnerRightHandAnimName = "otochlaven_shake";
				selectionFireAnim = "zasleh";
				minElev = -20;
				minTurn = -90;
				maxTurn = 90;
				weapons[] = {"BN_RHS_M2"};
				magazines[] = {"BN_100Rnd_127x99"};
				gunnerAction = "LowTripod_Gunner";
			};
		};
		
		class AnimationSources {
			class muzzleHMG_ROT {
				source = "ammorandom";
				weapon = "BN_RHS_M2";
			};
			class ReloadAnim {
				source = "reload";
				weapon = "BN_RHS_M2";
			};
 			class ReloadMagazine {
				source = "reloadmagazine";
				weapon = "BN_RHS_M2";
			}; 
			class Revolving {
				source = "revolving";
				weapon = "BN_RHS_M2";
			};
		}; 
	};
	class RHS_M2StaticMG_MiniTripodWD: RHS_M2StaticMG_MiniTripod_base {
		class Turrets: Turrets {
			class MainTurret: MainTurret {
				optics = 1;
				turretInfoType = "RscWeaponZeroing";
				discreteDistance[] = {100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500, 1600, 1700, 1800, 1900, 2000, 2100, 2200, 2300};
				discreteDistanceInitIndex = 2;
				gunnerOpticsModel = "\A3\weapons_f\reticle\optics_empty";
				gunnerLeftHandAnimName = "otochlaven_shake";
				gunnerRightHandAnimName = "otochlaven_shake";
				selectionFireAnim = "zasleh";
				minElev = -20;
				minTurn = -90;
				maxTurn = 90;
				weapons[] = {"BN_RHS_M2"};
				magazines[] = {"BN_100Rnd_127x99"};
				gunnerAction = "LowTripod_Gunner";
			};
		};
	};
	
	class RHS_M2StaticMG_MiniTripodD: RHS_M2StaticMG_MiniTripod_base {
		class Turrets: Turrets {
			class MainTurret: MainTurret {
				optics = 1;
				turretInfoType = "RscWeaponZeroing";
				discreteDistance[] = {100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500, 1600, 1700, 1800, 1900, 2000, 2100, 2200, 2300};
				discreteDistanceInitIndex = 2;
				gunnerOpticsModel = "\A3\weapons_f\reticle\optics_empty";
				gunnerLeftHandAnimName = "otochlaven_shake";
				gunnerRightHandAnimName = "otochlaven_shake";
				selectionFireAnim = "zasleh";
				minElev = -20;
				minTurn = -90;
				maxTurn = 90;
				weapons[] = {"BN_RHS_M2"};
				magazines[] = {"BN_100Rnd_127x99"};
				gunnerAction = "LowTripod_Gunner";
			};
		};
		
	};
};

