# UE5 GAS Code Samples

Selected Gameplay Ability System (GAS) code samples extracted from **Valkyrie's Legacy**, an Action RPG developed in Unreal Engine 5 using C++.

The purpose of this repository is to showcase real-world GAS architecture, gameplay abilities, attribute management and combat systems implemented in a production-style project.

## Topics Covered

### Gameplay Ability System

* Custom Ability System Component
* Gameplay Ability management
* Ability slots and equipment
* Ability progression and unlock systems
* Input handling through Gameplay Tags

### Attributes & Effects

* Custom Attribute Set
* Primary, Secondary and Vital Attributes
* Attribute replication
* Gameplay Effects
* Damage processing
* Experience and progression systems

### Gameplay Tags

* Centralized Gameplay Tag architecture
* Ability Tags
* Input Tags
* Status Tags
* Damage Types
* Resistances
* Cooldowns
* Combat Events

### Combat Systems

* Projectile-based abilities
* Dodge abilities
* Damage calculations
* Status effects
* Debuffs and resistances

### RPG Features

* Character progression
* Spell point upgrades
* Ability unlocking
* Ability equipment system

## Repository Structure

```text
AbilitySystem/
Attributes/
Abilities/
Calculations/
ExecutionCalculations/
```

## Featured Files

### AbilitySystem

* AuraAbilitySystemComponent
* AuraAbilitySystemLibrary
* AuraGameplayTags

### Attributes

* AuraAttributeSet

### Abilities

* AuraProjectileSpell
* AuraDodgeAbility

### Calculations

* MMC_MaxHealth
* ExecCalc_Damage

## Original Project

### Valkyrie's Legacy

https://store.steampowered.com/app/3136250/Valkyries_Legacy/

Action RPG developed in Unreal Engine 5 using C++ and Gameplay Ability System (GAS), featuring AI-driven enemies, Behavior Trees, EQS, combat systems, progression mechanics and modular gameplay architecture.

## Notes

This repository is intended as a code showcase and is not a standalone compilable Unreal Engine project.

Assets, Blueprints, maps and project-specific dependencies have been intentionally removed.
