# Proyecto Aplicativo: Directorio Telefónico con Historial

## Objetivo
Desarrollar un directorio telefónico que utilice HashTable y AVL para organizar contactos por letra inicial y mantener un historial temporal de los últimos contactos realizados.

## Contexto
Una empresa necesita un sistema de directorio telefónico que permita búsquedas rápidas por apellido y mantenga un registro temporal de los contactos más utilizados.

## Estructura del contacto
```cpp
struct Contact {
    string firstName;     // Nombre
    string lastName;      // Apellido
    string phoneNumber;   // Número telefónico
    string email;         // Correo electrónico
    string company;       // Empresa
};
```

## Requerimientos funcionales y de performance

### RF1: Búsqueda rápida por nombre completo
- **Funcionalidad**: Encontrar contacto específico por apellido y nombre
- **Entrada**: "García, María"
- **Proceso esperado**: Acceso directo por letra inicial → búsqueda exacta en conjunto ordenado
- **Performance requerido**: O(1) + O(log n)

### RF2: Búsqueda por prefijo de apellido
- **Funcionalidad**: Encontrar todos los contactos cuyo apellido comience con un prefijo
- **Entrada**: Todos los "Martín..." 
- **Proceso esperado**: Acceso por letra inicial → recorrido ordenado con corte eficiente
- **Performance requerido**: O(1) + O(log n + k) donde k es el número de resultados

### RF3: Gestión automática de contactos por uso
- **Funcionalidad**: Mantener contactos más utilizados y eliminar automáticamente los menos accedidos
- **Comportamiento**: Al buscar un contacto se reduce su probabilidad de ser eliminado
- **Límite**: Definir capacidad máxima del directorio (ej: 1000 contactos máximo)
- **Proceso esperado**: Cuando se alcance el límite, eliminar automáticamente el contacto menos usado
- **Performance requerido**: O(1) para reordenamiento por uso y O(log n) para eliminación

### RF4: Distribución eficiente por letra inicial
- **Funcionalidad**: Organización que reduzca el espacio de búsqueda
- **Requerimiento**: Distribución por letra inicial del apellido (26 buckets A-Z)
- **Performance requerido**: Acceso O(1) al subconjunto correspondiente

### RF5: Ordenamiento alfabético dentro de grupos
- **Funcionalidad**: Mantener orden alfabético por apellido, luego por nombre
- **Requerimiento**: Permitir búsquedas exactas y por prefijo usando recorrido ordenado
- **Performance requerido**: O(log n) para búsquedas dentro del grupo

## Implementación sugerida
```cpp
class PhoneDirectory {
private:
    // Estructuras de datos elegidas por el estudiante    
    int maxCapacity;     // Límite máximo de contactos
    
public:
    // Operaciones 
    bool addContact(const Contact& contact);
    bool removeContact(const string& lastName, const string& firstName);
    Contact* searchContact(const string& lastName, const string& firstName); // Auto-actualiza uso
    vector<Contact> searchByPrefix(char letter, const string& prefix);
};
```

> **Nota importante**: 
> - La estructura `Contact` NO puede ser modificada. 
> - La clase `PhoneDirectory` puede ser modificada y expandida según las estructuras de datos elegidas por el estudiante.
> - El AVL puede ser modificado para soportar key-value, pero debe realizarse una copia del código original y trabajar sobre esa copia.


## Entregables
- Código fuente con implementación completa
- Programa de demostración con menú interactivo e intuitivo que muestre todas las funcionalidades 
- Archivo de datos iniciales con al menos 100 contactos distribuidos



