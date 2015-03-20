private ["_gun","_player","_mags","_unload_time"];
_gun = _this select 0;
_player = _this select 1;
_mags = _gun magazinesTurret [0];
_unload_time = getNumber (configFile >> "CfgWeapons" >> weapons _gun select 0 >> "bn_csw_ReloadTime") / 2;

/* if (!(local _gun)) then  {	
	bn_csw_give_owner = [_player, _gun];
	publicVariableServer "bn_csw_give_owner";
	_timeout = time;
	waitUntil {sleep 0.1; (local _gun) || (time > _timeout + 10);};
};
if (!(local _gun)) exitWith {hint "Не удалось решить проблему локальности"}; */

if ((count _mags > 0) && (someAmmo _gun)) then {
	if ((_gun getVariable ["bn_csw_occupied",false]) || !(isNull (gunner _gun))) exitWith {hint "Орудие занято!"};
	_player playAction "Gear";
	_gun setVariable ["bn_csw_occupied",true,true];
	[_unload_time, [_player, _gun, _mags select 0], "{
		[_this,'remoteUnload', _this select 1] call BIS_fnc_MP;	
		
		private ['_player', '_gun', '_mags'];
		_player = _this select 0;
		_gun = _this select 1;
		_mag = _this select 2;
		
		_gun setVariable ['bn_csw_occupied',false,true];
		hint format ['Разряжено (%1)', getText (configFile >> 'CfgMagazines' >> (_mag) >> 'displayName')];
	}", "Разряжаю", "{_gun setVariable ['bn_csw_occupied',false,true]; hint 'Разряжание прервано'};"] call AGM_Core_fnc_progressBar;
} else {
	hint "Орудие не заряжено!";
};

/* _holder = objNull;
		_ammo_count = (_gun) magazineTurretAmmo [(_mag),[0]];
		_nearby = nearestObjects [_gun, ['GroundWeaponHolder'], 3];
		if (count _nearby > 0) then {_holder = _nearby select 0};
		if (isNull _holder) then {_holder = 'GroundWeaponHolder' createVehicle (getPos _gun);};
		_holder addMagazineAmmoCargo [(_mag), 1, _ammo_count];
		_pos = ((getPos _gun) vectorAdd ((vectorDir _gun) vectorMultiply -1));
		_holder setPosATL [_pos select 0, _pos select 1, (getPosATL _gun) select 2];
		(_gun) removeMagazineTurret [(_mag),[0]];
		if (!someAmmo _gun) then {_gun removeMagazinesTurret [(weapons _gun select 0),[0]];}; */